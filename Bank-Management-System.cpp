#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include<fstream>


using namespace std;
struct stClientData {
	string AcccountNumber, Name, Phone, PINCode;
	double balance = 0.0;
	bool mark = false;
};

enum enMainMenuAction { ListClients = 1, NewClient, DeleteClient, UpdateClient, FindClient, TransactionMenue, Exit };

enum enTransatcionMenueAction { Deposit = 1, WithDrawl, TotalBalances, MainMenue };

const string FileName = "Clients.txt";

bool isFound;

short EnterNumberWithCondition(short limit) {
	short number;
	cin >> number;
	while (number > limit || number < 1) {
		cout << "\nInvalid Input, Enter a Number from [1,2,3,4,5,6]\n";
		cin >> number;
	}
	return number;
}

string EnterAccountNumber(string message = "\nEnter Accont Number..\n") {
	string name;
	cout << message;;
	getline(cin >> ws, name);
	return name;
}

vector<string>  SplitString(string text, string delim) {
	string word = "";
	vector<string> vWords;

	short pos = 0;
	while ((pos = text.find(delim)) != std::string::npos) {
		word = text.substr(0, pos);
		if (word != " ")
			vWords.push_back(word);
		text = text.erase(0, pos + delim.length());
	}
	if (text != " ")

		vWords.push_back(text);
	return vWords;
}

stClientData ConvertClientDataLineIntoRecord(string line) {
	vector<string> vClientData = SplitString(line, "#//#");
	stClientData ClientData;
	ClientData.AcccountNumber = vClientData.at(0);
	ClientData.PINCode = vClientData.at(1);
	ClientData.Name = vClientData.at(2);
	ClientData.Phone = vClientData.at(3);
	ClientData.balance = stod(vClientData.at(4));

	return ClientData;

}

vector<stClientData> StoreFileInClientDataVector() {
	fstream File;
	vector<stClientData> vClientsData;
	string line;
	File.open(FileName, ios::in);
	if (File.is_open()) {
		while (getline(File, line))
		{
			if (line != "")
				vClientsData.push_back(ConvertClientDataLineIntoRecord(line));

		}
	}
	File.close();
	return vClientsData;
}

string ConvertDataRecordIntoLine(stClientData ClientData) {
	string ClientDataLine = "";
	ClientDataLine += ClientData.AcccountNumber + "#//#";
	ClientDataLine += ClientData.PINCode + "#//#";
	ClientDataLine += ClientData.Name + "#//#";
	ClientDataLine += ClientData.Phone + "#//#";
	ClientDataLine += to_string(ClientData.balance);
	return ClientDataLine;
}

string setw(short number, string delim) {
	string text = "";
	for (short i = 0; i < number; i++)
		text += delim;
	return text;
}

void TransactionMenueShape();

void WorkingInMainMenue(vector<stClientData>);

void WorkingWithTransactionMenue(vector<stClientData> vClients);

bool FindAccountByAccountNumberInFile(stClientData& WantedClient, vector<stClientData> vClients, string WantedAccountNumber) {
	for (stClientData& Client : vClients) {
		if (Client.AcccountNumber == WantedAccountNumber) {
			WantedClient = Client;
			return true;
		}
	}

	return false;
}

bool CheckAccountNumber(vector<stClientData>& vClients, string AccountNumber) {
	for (stClientData& Client : vClients) {
		if (Client.AcccountNumber == AccountNumber)
			return true;
	}
	return false;
}

void MainMenueShape() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Main Menue Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << setw(3, "	") << "[1] Show Client List." << "\n";
	cout << setw(3, "	") << "[2] Add New Client." << "\n";
	cout << setw(3, "	") << "[3] Delete Client." << "\n";
	cout << setw(3, "	") << "[4] Update Client Info." << "\n";
	cout << setw(3, "	") << "[5] Find Client." << "\n";
	cout << setw(3, "	") << "[6] Transaction Menue." << "\n";
	cout << setw(3, "	") << "[7] Exit." << "\n";
	cout << setw(40, "==") << "\n";

}

void EndScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Program Ends :)" << "\n\n";
	cout << setw(40, "==") << "\n";

}

void BackToTransactionMenue(vector<stClientData> vClients) {
	cout << "\nPress any key to back to the TransactionScreen...";
	system("pause > 0");
	WorkingWithTransactionMenue(vClients);

}

void BackToMainMenue(vector<stClientData> vClients) {
	cout << "\nPress any key to back to the TransactionScreen...";
	system("pause > 0");
	WorkingInMainMenue(vClients);

}

void PrintSingleClientDataAlone(stClientData ClientData) {
	cout << "\nAccount Details:\n";
	cout << left;
	cout << "Account Number: " << setw(10) << ClientData.AcccountNumber;
	cout << "\nPIN Code: " << setw(5) << ClientData.PINCode;
	cout << "\nClient Name: " << setw(20) << ClientData.Name;
	cout << "\nPhone Number: " << setw(10) << ClientData.Phone;
	cout << "\nBalance: " << setw(10) << ClientData.balance << endl;

}

void StoreVectorOfClientsInFile(vector<stClientData> vClients, string FileName) {
	fstream File;
	File.open(FileName, ios::out);
	if (File.is_open()) {
		for (stClientData Client : vClients)
		{
			if (!Client.mark)
				File << ConvertDataRecordIntoLine(Client) << endl;
		}
	}
	File.close();

}

void DeletClientFromFile(vector<stClientData>& vClients, string WantedAccountNumber) {

	stClientData DeleteThisClient;
	if (FindAccountByAccountNumberInFile(DeleteThisClient, vClients, WantedAccountNumber)) {
		PrintSingleClientDataAlone(DeleteThisClient);
		char answer;
		cout << "Do You Want to delete this client? Y or N\n";
		cin >> answer;
		if (tolower(answer) == 'y') {

			for (stClientData& Client : vClients) {
				if (Client.AcccountNumber == DeleteThisClient.AcccountNumber) {
					Client.mark = true;
					break;
				}
			}
			StoreVectorOfClientsInFile(vClients, FileName);
			vClients = StoreFileInClientDataVector();
			cout << "\nClient Deleted Successfully\n";
		}

	}
	else

		cout << "\nAccount was not found\n";
}

void EnterClientData(stClientData& ClientData, vector<stClientData> vClients) {
	stClientData Client;
	cout << "Enter Account Number:\n";
	getline(cin >> ws, ClientData.AcccountNumber);
	while (FindAccountByAccountNumberInFile(Client, vClients, ClientData.AcccountNumber)) {
		cout << "\nThis Account Number is already Exist, Enter another one...\n";
		getline(cin >> ws, ClientData.AcccountNumber);
	}
	cout << "Enter PIN code:\n";
	getline(cin, ClientData.PINCode);
	cout << "Enter User's Name:\n";
	getline(cin, ClientData.Name);
	cout << "Enter Phone Number:\n";
	getline(cin, ClientData.Phone);
	cout << "Enter account's balance\n";
	cin >> ClientData.balance;
}

void UpdateSingleClientData(stClientData& ThisClient) {
	cout << "\nUpdate PIN code:\n";
	getline(cin >> ws, ThisClient.PINCode);
	cout << "Update User's Name:\n";
	getline(cin, ThisClient.Name);
	cout << "Update Phone Number:\n";
	getline(cin, ThisClient.Phone);
	cout << "Update account's balance\n";
	cin >> ThisClient.balance;
}

void UpdateClientUsingAccountNumber(string AccounNumber, vector<stClientData>& vClients) {
	stClientData ThisClient;
	char Answer;
	if (FindAccountByAccountNumberInFile(ThisClient, vClients, AccounNumber)) {
		PrintSingleClientDataAlone(ThisClient);
		cout << "\nDo you want to Update This Account Data?\n Y for yes and N for No\n";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			UpdateSingleClientData(ThisClient);
			for (stClientData& Client : vClients)
			{
				if (Client.AcccountNumber == ThisClient.AcccountNumber) {
					Client = ThisClient;
					break;
				}
			}
			StoreVectorOfClientsInFile(vClients, FileName);
			cout << "\nClients Data have been updated Successfully!\n";
		}

	}

	else {
		cout << "\nClient with Account Number (" << AccounNumber << ") was not found!\n";
	}
}

void UpdateSpecifiClientInVector(stClientData ThisClient, vector<stClientData>& vClients) {
	for (stClientData& Client : vClients) {
		if (Client.AcccountNumber == ThisClient.AcccountNumber) {
			Client = ThisClient;
			break;
		}


	}
}

void PrintSingleClientData(stClientData ClientData) {
	cout << left;
	cout << "| " << setw(20) << ClientData.AcccountNumber;
	cout << "| " << setw(15) << ClientData.PINCode;
	cout << "| " << setw(30) << ClientData.Name;
	cout << "| " << setw(20) << ClientData.Phone;
	cout << "| " << setw(20) << ClientData.balance << endl;

}

void PrintSingleClientData2(stClientData ClientData) {
	cout << left;
	cout << "| " << setw(20) << ClientData.AcccountNumber;
	cout << "| " << setw(15) << ClientData.PINCode;
	cout << "| " << setw(30) << ClientData.Name;
	cout << "| " << setw(15) << ClientData.balance;
	cout << "\n";


}

void GeneralShape(short number) {
	cout << setw(60) << "Client List(" << number << ") Client(s)";
	cout << "\n" << setw(55, "__") << "\n\n";
	cout << left;
	cout << "| " << setw(20) << "Account Number";
	cout << "| " << setw(15) << "PIN Code";
	cout << "| " << setw(30) << "Client Name";
	cout << "| " << setw(20) << "Phone Number";
	cout << "| " << setw(20) << "Balance";
	cout << "\n" << setw(55, "__") << "\n\n";
}

void GeneralShape2(short number) {
	cout << setw(26, " ") << "Client List(" << number << ") Client(s)";
	cout << "\n" << setw(55, "__") << "\n\n";
	cout << left;
	cout << "| " << setw(20) << "Account Number";
	cout << "| " << setw(15) << "PIN Code";
	cout << "| " << setw(30) << "Client Name";
	cout << "| " << setw(15) << "Balance ";
	cout << "\n" << setw(55, "__") << "\n\n";
}

void PrintAllClientsData() {

	vector<stClientData> vClientsData = StoreFileInClientDataVector();
	GeneralShape(vClientsData.size());
	for (stClientData& Client : vClientsData)
	{
		PrintSingleClientData(Client);
	}
	cout << "\n" << setw(55, "__") << "\n\n";
	BackToMainMenue(vClientsData);
}

void PrintAllClientsData2(vector<stClientData> vClients) {

	GeneralShape2(vClients.size());
	for (stClientData& Client : vClients)
	{
		PrintSingleClientData2(Client);
	}
	cout << "\n" << setw(55, "__") << "\n\n";
}

void StoreClientDataLineInFile(string FileName, string ClientDataLine, vector<stClientData>& vClients) {
	fstream File;
	File.open(FileName, ios::out | ios::app);
	if (File.is_open())
		if (ClientDataLine != "")
			File << ClientDataLine << endl;
	File.close();
	vClients = StoreFileInClientDataVector();

}

void AddNewClient(vector<stClientData> vClients) {
	stClientData ClientData;
	EnterClientData(ClientData, vClients);
	StoreClientDataLineInFile(FileName, ConvertDataRecordIntoLine(ClientData), vClients);

}

void EnterManyClientsData(vector<stClientData>& vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Add Clients Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	char AddMore = ' ';
	do
	{

		cout << "Add new Client: \n";
		AddNewClient(vClients);
		cout << "Client Added Successfully, Do you want to add more client?\nY for yes and N for no\n";
		cin >> AddMore;
	} while (AddMore == 'Y' || AddMore == 'y');
	vClients = StoreFileInClientDataVector();
	BackToMainMenue(vClients);

	system("cls");
}

void AccountFoundOrNotOutput(stClientData OurClient, string WantedNumber, bool result) {

	if (result) {
		cout << "\nAccount with Account Number (" << WantedNumber << ") was found\n";
		PrintSingleClientDataAlone(OurClient);
	}
	else {
		cout << "\nAccount with Account Number (" << WantedNumber << ") was not found\n";
	}
}

void DeleteClientScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Clients Delete Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	DeletClientFromFile(vClients, EnterAccountNumber());
	BackToMainMenue(vClients);

}

void UpdateClientScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Update Clients Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	UpdateClientUsingAccountNumber(EnterAccountNumber(), vClients);
	BackToMainMenue(vClients);

}

void FindClientScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Find Client Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	stClientData OurClient;
	AccountFoundOrNotOutput(OurClient, OurClient.AcccountNumber, FindAccountByAccountNumberInFile(OurClient, vClients, EnterAccountNumber()));
	BackToMainMenue(vClients);
}

void DepositOperation(stClientData& ThisClient, vector<stClientData>& vClients) {
	double DepositValue;
	char answer;
	cout << "The Account was found...\n";
	PrintSingleClientDataAlone(ThisClient);
	cout << "\nPlease Enter how much you want to Deposit\n";
	cin >> DepositValue;
	cout << "Are you sure you want to do this deposit? Y for YES and N for NO\n";
	cin >> answer;

	if (tolower(answer) == 'y') {
		ThisClient.balance += DepositValue;
		cout << "Deposit Completed Successfully, New Balance is: " << ThisClient.balance << endl;

	}
	else {
		BackToTransactionMenue(vClients);

	}
}

void DepositAction(string AccountNumber, vector<stClientData>& vClients) {
	char answer;
	while (!CheckAccountNumber(vClients, AccountNumber)) {
		cout << "The Account was not found...\n";
		cout << "Enter Another Account Number....\n";
		cin >> AccountNumber;
	}
	for (stClientData& Client : vClients)
	{
		if (Client.AcccountNumber == AccountNumber) {

			DepositOperation(Client, vClients);
			UpdateSpecifiClientInVector(Client, vClients);
			StoreVectorOfClientsInFile(vClients, FileName);
			break;
		}
	}

	BackToTransactionMenue(vClients);


}

void DepositScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Deposit Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	DepositAction(EnterAccountNumber(), vClients);


}

void WithDawlOperation(stClientData& ThisClient, vector<stClientData>& vClients)
{
	double WithDrawlValue;
	char answer;
	cout << "The Account was found...\n";
	PrintSingleClientDataAlone(ThisClient);
	cout << "\nPlease Enter how much you want to Withdrawl\n";
	cin >> WithDrawlValue;
	while (WithDrawlValue > ThisClient.balance) {
		cout << "\nSorry, you do not have this ammount in your account, your balance is " << ThisClient.balance;
		cout << "\nEnter another ammount:...\n";
		cin >> WithDrawlValue;
	}
	cout << "Are you sure you want to do this Withdrawl? Y for YES and N for NO\n";
	cin >> answer;

	if (tolower(answer) == 'y') {
		ThisClient.balance -= WithDrawlValue;
		cout << "Withdrawl Completed Successfully, New Balance is: " << ThisClient.balance << endl;

	}
	else
		BackToTransactionMenue(vClients);

}

void WithDrawlAction(string AccountNumber, vector<stClientData> vClients) {
	char answer;
	while (!CheckAccountNumber(vClients, AccountNumber)) {
		cout << "The Account was not found...\n";
		cout << "Enter Another Account Number....\n";
		cin >> AccountNumber;

	}
	for (stClientData& Client : vClients)
	{
		if (Client.AcccountNumber == AccountNumber) {

			WithDawlOperation(Client, vClients);
			UpdateSpecifiClientInVector(Client, vClients);
			StoreVectorOfClientsInFile(vClients, FileName);
			break;
		}

	}

	BackToTransactionMenue(vClients);


}

void WithDrawlScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Withdrawl Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	WithDrawlAction(EnterAccountNumber(), vClients);
}

void TotalBalancesAction(vector<stClientData> vClients) {
	double TotalBalances = 0.0;
	PrintAllClientsData2(vClients);
	for (stClientData& Client : vClients)
		TotalBalances += Client.balance;
	cout << "\nTotal Balances is: " << TotalBalances << endl;

	BackToTransactionMenue(vClients);


}

void TotalBalancesScreen(vector<stClientData> vClients) {
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Total Balances Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	TotalBalancesAction(vClients);

}

void WorkingWithTransactionMenue(vector<stClientData> vClients) {
	enTransatcionMenueAction TransactionMenueAction;
	TransactionMenueShape();
	cout << "Choose What do you want to do from [ 1 to 4 ] " << endl;
	TransactionMenueAction = enTransatcionMenueAction(EnterNumberWithCondition(4));
	switch (TransactionMenueAction)
	{
	case Deposit:
		system("cls");
		DepositScreen(vClients);
		break;
	case WithDrawl:
		system("cls");
		WithDrawlScreen(vClients);
		break;
	case TotalBalances:
		system("cls");
		TotalBalancesScreen(vClients);
		break;
	case MainMenue:
		WorkingInMainMenue(vClients);
		break;

	}
}

void WorkingInMainMenue(vector<stClientData> vClients) {
	enMainMenuAction MainMenueAction;
	MainMenueShape();
	cout << "Choose What do you want to do from [ 1 to 7 ] " << endl;
	MainMenueAction = enMainMenuAction(EnterNumberWithCondition(7));
	switch (MainMenueAction)
	{
	case ListClients:
		system("cls");
		PrintAllClientsData();
		break;
	case NewClient:
		system("cls");
		EnterManyClientsData(vClients);
		break;
	case DeleteClient:
		system("cls");
		DeleteClientScreen(vClients);
		break;
	case UpdateClient:
		system("cls");
		UpdateClientScreen(vClients);
		break;
	case FindClient:
		system("cls");
		FindClientScreen(vClients);
		break;
	case TransactionMenue:
		WorkingWithTransactionMenue(vClients);
		break;
	case Exit:
		EndScreen();
		break;
	}

}

void TransactionMenueShape() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Transaction Menue Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << setw(3, "	") << "[1] Deposit." << "\n";
	cout << setw(3, "	") << "[2] Withdrawl." << "\n";
	cout << setw(3, "	") << "[3] Total Balances." << "\n";
	cout << setw(3, "	") << "[4] Main Menue." << "\n";
	cout << setw(40, "==") << "\n";

}

int main() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	WorkingInMainMenue(vClients);
	return 0;
}