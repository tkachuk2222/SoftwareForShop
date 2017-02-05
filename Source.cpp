#include<iostream>
#include<memory>
#include<string>
#include<exception>
#include<vector>
#include"List.h"
#include"Cassa.h"
#include"personal.h"
#include"products.h"
#include"storage.h"
#include"Market.h"




using namespace std;

int passDir = 1111;
int passAdm = 1111;
int passCas = 1111;
int enterPass();
int percentDisc = 10;

void openWriteInFile(FILE *f, const char* nameFile, int newPass);
int openFileAndReadPass(FILE *f, const char* nameFile);

void main() {
	shared_ptr<Market>market(Market::getMarket());
	//Market *market = Market::getMarket();
	FILE *f;
	printf("1\t\t\tsdfgsdfgsdfgsdfgsdfgsf2\t\t123\t\t2\n");
	printf("1\t\t\tf2\t\t123\t\t2\n");

	const char* passD = "director.txt";
	const char* passA = "admin.txt";
	const char* passC = "cashier.txt";

	fopen_s(&f, passD, "wb+");
	if (&f)
		fwrite(&passDir, sizeof(int), 1, f);
	fclose(f);

	fopen_s(&f, passA, "wb+");
	if (&f)
		fwrite(&passAdm, sizeof(int), 1, f);
	fclose(f);

	fopen_s(&f, passC, "wb+");
	if (&f)
		fwrite(&passCas, sizeof(int), 1, f);
	fclose(f);

	bool exit = true;

	while (true) {
		cout << "Who are you?\n";
		cout << "\t1. Director\n" <<
			"\t2. Admin\n" <<
			"\t3. Cashier\n" <<
			"\t4. Client\n" <<
			"\t5. Exit\n";
		int choose;
		cin >> choose;
		switch (choose)
		{
		case 1: {
			int pass = enterPass();
			if (pass == ::passDir) {
				cout << "1. Add product to store\n2. Add cash register to market\n3. Delete poduct\n";
				int choose;
				cin >> choose;
				switch (choose)
				{
				case 1: {
					cout << "1.Bread\n2.Water\n3.Alcohol\n4.Cookies\n5.Big cookies\n6.Dark Beer\n7.Rice\n";
					int prod;
					cin >> prod;
					market->addProdToStor(prod);
					break;
				}
				case 2: {
					cout << "How much cass add to market?\n";
					int countOfCass;
					cin >> countOfCass;
					market->addCassInStore(countOfCass);
					break;
				}
				case 3: {
					cout << "Whitch product delete?\n";
					market->showProdInMarket();
					int numOfProd;
					cin >> numOfProd;
					market->delProduct(numOfProd);
					break;
				}
				}
			}
			else {

			}
			break;
		}
		case 2: {
			int pass = enterPass();
			if (pass == ::passAdm) {
				cout << "1.Password change\n2.Show passwords\n";
				int chooseAdm;
				cin >> chooseAdm;
				if (chooseAdm == 1) {
					int changePass;
					cout << "whose change password?\n1.Director\n2.Admin\n3.Cashier\n";
					cin >> changePass;
					cout << "Enter new password\n";
					int newPass;
					cin >> newPass;
					if (changePass == 1) {
						openWriteInFile(f, passD, newPass);
						::passDir = newPass;
					}
					else if (changePass == 2) {
						openWriteInFile(f, passA, newPass);
						::passAdm = newPass;
					}
					else if (changePass == 3) {
						openWriteInFile(f, passC, newPass);
						::passCas = newPass;
					}
				}
				else {
					cout << "Password of director\t " << openFileAndReadPass(f, passD) << endl;
					cout << "Password of admin\t " << openFileAndReadPass(f, passA) << endl;
					cout << "Password of cashier\t " << openFileAndReadPass(f, passC) << endl;
				}
			}
			else {

			}
			break;
		}
		case 3: {
			int pass = enterPass();
			if (pass == ::passCas) {
				cout << "1. Sell product\n2. Cash balance\n3. Add discount card\n";
				int chooseCass;
				cin >> chooseCass;
				switch (chooseCass)
				{
				case 1: {
					int product, cnt, numCas;
					bool yes = true;
					try {
						while (yes) {
							if (market->isEmpty())
								throw "\tError!! Shop haven't cash register!\n";
							market->showProdInMarket();
							cout << "What product?";
							cin >> product;
							cout << "How many?" << endl;
							cin >> cnt;
							cout << "Number of cashier" << endl;
							cin >> numCas;
							if (numCas > market->getCntOfCashRegister())
								throw numCas;
							cout << "Discount card?\n 1 - yes\n0 - no\n" << endl;
							bool existDiscount = false;
							cin >> existDiscount;
							
							market->sellProd(product - 1, cnt, numCas, existDiscount, ::percentDisc);
							cout << "Continue selling? 1 - yes 0 - no \n";
							cin >> yes;
						}
					}
					catch (const char*ex) {
						cout << ex << endl;
					}
					catch (int numCas) {
						cout << "\tShop haven't " << numCas << " cash register!!\n \t\tAvailable " << market->getCntOfCashRegister() << " cash register\n";
					}
					break;
				}
				case 2: {
					try {
						if (market->isEmpty())
							throw "\tError!! Shop haven't cash register!\n";
						cout << "1.Show cash on hand\n2.Withdraw cash from the cash register\n";
						int chooseCass;
						cin >> chooseCass;
						switch (chooseCass)
						{
						case 1: {
							market->showCashInCass();
							break;
						}
						case 2: {
							cout << "From which cash register?\n";
							market->showCashInCass();
							int numbCass;
							cin >> numbCass;
							market->cashInCassToZero(numbCass);
							break;
						}
						}
					}
					catch (const char*ex) {
						cout << ex << endl;
					}
					break;
				}
				case 3: {
					cout << "Enter the ID of the new card\n";
					double newCardId;
					cin >> newCardId;
					market->addDiscountCard(newCardId);
					break;
				}
				}
			}
			else {

			}
			break;
		}
		case 4: {
			int product, cnt, numCas;
			double totalSum = 0;
			double discountNumb;
			bool yes = true;
			double cardID;
			cout << "You have a discount card?\n 1 - yes\n0 - no\n" << endl;
			bool existDiscount = false;
			cin >> existDiscount;

			if (existDiscount) {
				cout << "Enter the number of card\n";
				
				cin >> cardID;
				existDiscount = market->isExistDiscount(cardID);
				if (!existDiscount)
					cout << "Sorry, but we haven't card with this number\n";
			}
				try {
					while (yes) {
						if (market->isEmpty())
							throw "\tError!! Shop haven't cash register!\n";
						market->showProdInMarket();
						cout << "What product you want to buy?";
						cin >> product;
						cout << "How many?" << endl;
						cin >> cnt;
						cout << "Number of cashier" << endl;
						cin >> numCas;
						if (numCas > market->getCntOfCashRegister())
							throw numCas;
						market->sellProd(product - 1, cnt, numCas, existDiscount, ::percentDisc);
						totalSum += market->getTotalPriceOfPurchase(product - 1, cnt, existDiscount, ::percentDisc);

						cout << "Continue purchase? 1 - yes 0 - no \n";
						cin >> yes;
					}

				}
				catch (const char*ex) {
					cout << ex << endl;
				}
				catch (int numCas) {
					cout << "\tShop haven't " << numCas << " cash register!!\n \t\tAvailable " << market->getCntOfCashRegister() << " cash register\n";
				}
				cout << "Total price is " << totalSum << "$" << endl;
				break;
			}
		case 5: {
			//exit(0);
			return;
		}
		}
				cout << "continue? \n1 - yes \n0 - no" << endl;
				cin >> exit;
				system("cls");
		}





	}



int enterPass() {
	cout << "enter password:\n";
	int pass;
	cin >> pass;
	return pass;
}

void openWriteInFile(FILE *f, const char* nameFile, int newPass) {
	fopen_s(&f, nameFile, "wb+");
	if (f)
		fwrite(&newPass, sizeof(int), 1, f);
	fclose(f);
}

int openFileAndReadPass(FILE *f, const char* nameFile) {
	if (f) {
		fopen_s(&f, nameFile, "rb");
		int tmpPass;
		fread(&tmpPass, sizeof(int), 1, f);
		return tmpPass;
	}
	return 0;
}

//	Cookies coo{ "dfghdfg", 345, 345,"sdfgh" };

//Storage st;
//
//st.addProd(new Alcohol(20, "hren'", 1234, 123, 1, 40));
//st.addProd(new Water(30, "mineral", 343434, 29, 5));
//st.addProd(new Water(30, "mineral nn", 3434, 9, 5));

//st.addCassInStore(new Cass());
//st.addCassInStore(new Cass());

//st.showProd();	//how to show?
//st.sellProd(1, 3, 1);
//cout << "del prod " << 1 << endl;
//st.showProd();




/*List<int>lt;
lt.addToBegin(4564);
lt.show();*/