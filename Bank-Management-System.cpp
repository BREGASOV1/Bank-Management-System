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
struct stUser {
	string Name = "";
	string PassWord = "";
	short permissions = 0;
};

enum enMainMenuAction { ListClients = 1, NewClient, DeleteClient, UpdateClient, FindClient, TransactionMenue,ManageUsers, LoginPage };

enum enTransatcionMenueAction { Deposit = 1, WithDrawl, TotalBalances, MainMenue };

enum enManageUsersMenueAction{ ListUsers = 1, NewUser, DeleteUser, UpdateUser, FindUser,MainMenue1 };

enum enMainMenuePermissions{pAll = -1, 
	pListClients = 1, pAddClients = 2, pDeleteClient = 4,
	pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers =64	};

stUser LoginUser;
const string FileName = "Clients.txt";
const string UsersFile = "Users.txt";

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

stUser ConvertUserLineIntoRecord(string line) {
	vector<string> vUser = SplitString(line, "#//#");
	stUser User;
	User.Name = vUser.at(0);
	User.PassWord = vUser.at(1);
	User.permissions =(short) stoi(vUser.at(2));

	return User;

}

string ConvertUserInfoToStringLine(stUser User) {
	string UserInfoLine = "";
	UserInfoLine += User.Name + "#//#";
	UserInfoLine += User.PassWord + "#//#";
	UserInfoLine += to_string(User.permissions);
	return UserInfoLine;

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

vector<stUser> StoreFileInUsersVector() {
	fstream File;
	vector<stUser> vUsers;
	string line;
	File.open(UsersFile, ios::in);
	if (File.is_open()) {
		while (getline(File, line))
		{
			if (line != "")
				vUsers.push_back(ConvertUserLineIntoRecord(line));

		}
	}
	File.close();
	return vUsers;
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

void StoreVectorOfUsersInFile(vector<stUser>& vUsers) {
	fstream File;
	File.open(UsersFile, ios::out);
	for (stUser& user : vUsers) {
		if (user.Name != "")
			File << ConvertUserInfoToStringLine(user) << endl;
	}
	File.close();
	vUsers = StoreFileInUsersVector();



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

void StoreClientDataLineInFile(string FileName, string ClientDataLine, vector<stClientData>& vClients) {
	fstream File;
	File.open(FileName, ios::out | ios::app);
	if (File.is_open())
		if (ClientDataLine != "")
			File << ClientDataLine << endl;
	File.close();
	vClients = StoreFileInClientDataVector();

}

string setw(short number, string delim) {
	string text = "";
	for (short i = 0; i < number; i++)
		text += delim;
	return text;
}

stUser FindUserWithUserName(string username) {
	vector<stUser> vUsers = StoreFileInUsersVector();
	for (stUser& user : vUsers)
		if (user.Name == username) {
			return user;
			break;
		}
}

void WorkingInManageUsersMenue();

void WorkingInMainMenue();

void WorkingWithTransactionMenue();

void LoginOperation();

void AccessDenied() {
	system("cls");
	vector<stClientData> vClients = StoreFileInClientDataVector();
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Access Denied" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << "You do not have the permission to do this action.....\n";
	cout << "Contact your admin....\n";
	cout << "\nPress any key to go back to Main Menue...."<<endl;
	system("pause>0");
	WorkingInMainMenue();


}

bool HavePermission(enMainMenuePermissions Permission) {
	if (LoginUser.permissions == pAll)
		return true;
	else
		return((LoginUser.permissions & Permission) == Permission);
}

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

bool CheckUser(stUser User) {
	vector<stUser> vUsers = StoreFileInUsersVector();
	
	for (stUser& user : vUsers) {
		if (user.Name == User.Name && user.PassWord == User.PassWord) {
			return true;
			break;
		}
	}

	return false;
	
}

bool CheckUserName(string username) {
	vector<stUser> vUsers = StoreFileInUsersVector();

	for (stUser& user : vUsers) {
		if (user.Name == username){
			return true;
		
	}
}
	return false;

}

void LoginInterface() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Login Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	LoginOperation();
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

void LoginOperation() {
	cout << "\nEnter User Name:......\n";
	getline(cin >> ws, LoginUser.Name);
	cout << "\nEneter User Password:...\n";
	getline(cin >> ws, LoginUser.PassWord);
	while (!CheckUser(LoginUser)) {
		cout << "\nLogin Failed, wrong password or username...!!\n";
		cout << "\npress any key to login again";
		system("pause>0");
		LoginInterface();
	}
	LoginUser.permissions = FindUserWithUserName(LoginUser.Name).permissions;
	WorkingInMainMenue();
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
	cout << setw(3, "	") << "[7] Manage Users." << "\n";
	cout << setw(3, "	") << "[8] LogOut." << "\n";
	cout << setw(40, "==") << "\n";

}

void ManageUserMenueShape() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Manage Users Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << setw(3, "	") << "[1] Show Users List." << "\n";
	cout << setw(3, "	") << "[2] Add New User." << "\n";
	cout << setw(3, "	") << "[3] Delete User." << "\n";
	cout << setw(3, "	") << "[4] Update User Info." << "\n";
	cout << setw(3, "	") << "[5] Find User." << "\n";
	cout << setw(3, "	") << "[6] MainMenue." << "\n";
	cout << setw(40, "==") << "\n";

}

void BackToTransactionMenue() {
	cout << "\nPress any key to back to the TransactionScreen...";
	system("pause > 0");
	WorkingWithTransactionMenue();

}

void BackToMainMenue() {
	cout << "\nPress any key to back to the Main Menue...";
	system("pause > 0");
	WorkingInMainMenue();

}

void BackToManageUsersMenue() {
	cout << "\nPress any key to go back to Manage Users Menue......";
	system("pause>0");
	WorkingInManageUsersMenue();
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

void DeletClientFromFile( string WantedAccountNumber) {
	vector<stClientData> vClients = StoreFileInClientDataVector();
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

void UpdateClientUsingAccountNumber(string AccounNumber) {
	vector<stClientData> vClients = StoreFileInClientDataVector();
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

void PrintOneUser(stUser User) {
	cout << left;
	cout << "| " << setw(20) << User.Name;
	cout << "| " << setw(15) << User.PassWord;
	cout << "| " << setw(30) << User.permissions << endl;
}

void PrintAllUsersScreen() {
	system("cls");
	vector<stUser> vUsers = StoreFileInUsersVector();
	cout <<right<< setw(30) << "Users List  [" << vUsers.size() << "]";
	cout << "\n" << setw(55, "__") << "\n\n";
	cout << left;
	cout << "| " << setw(20) << "User Name";
	cout << "| " << setw(15) << "Password";
	cout << "| " << setw(30) << "Permissions";
	cout << "\n" << setw(55, "__") << "\n\n";
	for (stUser& user : vUsers)
		PrintOneUser(user);
	cout << "\n" << setw(55, "__") << "\n\n";
	BackToManageUsersMenue();
}

void PrintAllClientsData() {
	if (!HavePermission(pListClients)) {
		AccessDenied();
		
	}
	vector<stClientData> vClientsData = StoreFileInClientDataVector();
	GeneralShape(vClientsData.size());
	for (stClientData& Client : vClientsData)
	{
		PrintSingleClientData(Client);
	}
	cout << "\n" << setw(55, "__") << "\n\n";
	BackToMainMenue();
}

void PrintAllClientsData2(vector<stClientData> vClients) {

	GeneralShape2(vClients.size());
	for (stClientData& Client : vClients)
	{
		PrintSingleClientData2(Client);
	}
	cout << "\n" << setw(55, "__") << "\n\n";
}

void AddNewClient() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	stClientData ClientData;
	EnterClientData(ClientData, vClients);
	StoreClientDataLineInFile(FileName, ConvertDataRecordIntoLine(ClientData), vClients);
	

}

void EnterManyClientsData() {
	if(!HavePermission(pAddClients)) {
		AccessDenied();
		
	}
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Add Clients Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	char AddMore = ' ';
	do
	{

		cout << "Add new Client: \n";
		AddNewClient();
		cout << "Client Added Successfully, Do you want to add more client?\nY for yes and N for no\n";
		cin >> AddMore;
	} while (AddMore == 'Y' || AddMore == 'y');
	
	BackToMainMenue();

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

void DeleteClientScreen() {
	if (!HavePermission(pDeleteClient)) {
		AccessDenied();
		
	}
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Clients Delete Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	DeletClientFromFile( EnterAccountNumber());
	BackToMainMenue();

}

void UpdateClientScreen() {
	if (!HavePermission(pUpdateClient)) {
		AccessDenied();
		
	}
	vector<stClientData> vClients = StoreFileInClientDataVector();
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Update Clients Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	UpdateClientUsingAccountNumber(EnterAccountNumber());
	BackToMainMenue();

}

void FindClientScreen() {
	if (!HavePermission(pFindClient)) {
		AccessDenied();
		
	}
	vector<stClientData> vClients = StoreFileInClientDataVector();
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Find Client Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	stClientData OurClient;
	AccountFoundOrNotOutput(OurClient, OurClient.AcccountNumber, FindAccountByAccountNumberInFile(OurClient, vClients, EnterAccountNumber()));
	BackToMainMenue();
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
		BackToTransactionMenue();

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

	BackToTransactionMenue();


}

void DepositScreen() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
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
		BackToTransactionMenue();

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

	BackToTransactionMenue();


}

void WithDrawlScreen() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
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

	BackToTransactionMenue();


}

void TotalBalancesScreen() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Total Balances Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	TotalBalancesAction(vClients);

}

short CalculateUserPermissions() {
	short permissions = 0;
	char answer;
	cout << "\Do you want to give access to Show Clients? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pListClients : permissions += 0;
	cout << "\Do you want to give access to Add Client? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pAddClients : permissions += 0;
	cout << "\Do you want to give access to Delete Client? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pDeleteClient : permissions += 0;
	cout << "\Do you want to give access to Update Client? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pUpdateClient : permissions += 0;
	cout << "\Do you want to give access to Find Client? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pFindClient : permissions += 0;
	cout << "\Do you want to give access to Tansactions? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pTransactions : permissions += 0;
	cout << "\Do you want to give access to Manage Users? Y/N";
	cin >> answer;
	(tolower(answer) == 'y') ? permissions += pManageUsers : permissions += 0;
	return permissions;
}

stUser EnterUserInfo() {
	stUser user;
	char answer;
	cout << "\nEnter User Name...\n";
	cin >> user.Name;
	while (CheckUserName(user.Name)) {
		cout << "\nThis user name is already exixt...";
		cout << "\nEnter User Name...\n";
		cin >> user.Name;
	}
	cout << "\nEnter User PassWord....\n";
	cin >> user.PassWord;
	cout << "\nDo you want to give this user all permisions? Y/N\n";
	cin >> answer;
	(tolower(answer) == 'y') ? user.permissions = pAll : user.permissions = CalculateUserPermissions();
	return user;
}

stUser  UpdateUserInfo(string username) {
	stUser user;
	char answer;
	user.Name = username;
	cout << "\nUpdate User PassWord....\n";
	cin >> user.PassWord;
	cout << "\nUpdateing Permissions\nDo you want to give this user all permisions? Y/N\n";
	cin >> answer;
	(tolower(answer) == 'y') ? user.permissions = pAll : user.permissions = CalculateUserPermissions();
	return user;
}

void AddManyUsers(vector<stUser>& vUsers) {

	char answer;
	do
	{
		cout << "\nEnter User Info:\n";
		vUsers.push_back(EnterUserInfo());
		StoreVectorOfUsersInFile(vUsers);
		cout << "\nUser has been added successfully....";
		cout << "\nDo you want to add another user? Y/N\n";
		cin >> answer;
	} while (tolower(answer) == 'y');

	BackToManageUsersMenue();
}

void AddNewUserScreen() {
	system("cls");
	vector<stUser> vUsers = StoreFileInUsersVector();
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Add Users Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	AddManyUsers(vUsers);
}

void DeleteOneUser(vector<stUser>& vUsers) {
	string username;
	cout << "\nEnter The user name you want to delete...\n";
	cin >> username;
	if (!CheckUserName(username)) {
		cout << "\nThis user name is not exist";
		cout << "\nEnter The user name you want to delete...\n";
		cin >> username;
	}

	if (username == "Admin") {
		cout << "\nYou can not delete an admin user...\n";
	}
	else {
		for (stUser& user : vUsers)
			if (user.Name == username)
				user.Name = "";
		StoreVectorOfUsersInFile(vUsers);
		cout << "\nUser has been deleted successfully....\n";
	}
}

void DeleteManyUsers() {
	vector<stUser> vUsers = StoreFileInUsersVector(); char answer;
	do
	{
		cout << "\nEnter User Info:\n";
		DeleteOneUser(vUsers);
		cout << "\nDo you want to delete another user? Y/N\n";
		cin >> answer;
	} while (tolower(answer) == 'y');
	BackToManageUsersMenue();
}

void DeleteUsersScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Delete Users Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	DeleteManyUsers();
}

void UpdateOneUser(vector<stUser> vUsers) {
	string username;
	cout << "\Enter The user name you want to Update his\\her info...\n";
	cin >> username;
	while (!CheckUserName(username)) {
		cout << "\nThis user name is not exist";
		cout << "\nEnter The user name you want to Update his\\her info...\n";
		cin >> username;
	}
	if (username == "Admin") {
		cout << "\nYou can not update an admin user...\n";
	}
	else {
		for (stUser& user : vUsers)
			if (user.Name == username) {
				user = UpdateUserInfo(username);
			}
		StoreVectorOfUsersInFile(vUsers);
		cout << "\nUser info has been updated successfull.....";
	}
}

void UpdateManyUsers() {
	vector<stUser> vUsers = StoreFileInUsersVector(); char answer;
	do
	{
		cout << "\nEnter User Info:\n";
		UpdateOneUser(vUsers);
		cout << "\nDo you want to Update another user? Y/N\n";
		cin >> answer;
	} while (tolower(answer) == 'y');
	BackToManageUsersMenue();
}

void UpdateUsersScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Update Users Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	UpdateManyUsers();
}

void PrintUserInfo(stUser user) {
	cout << "\nUser info:";
	cout << left;
	cout << setw(21) << "\nUser Name: " << user.Name;
	cout << setw(21) << "\nUser Password: " << user.PassWord;
	cout << setw(21) << "\nUser Permissions: " << user.permissions;
}

void FindManyUsers() {

	char answer;
	string username;
	do
	{
		cout << "\nEnter User name:\n";
		cin >> username;
		if (CheckUserName(username))
			PrintUserInfo(FindUserWithUserName(username));
		else
			cout << "\nUser is not foud...";
		cout << "\nDo you want to Search another user? Y/N\n";
		cin >> answer;
	} while (tolower(answer) == 'y');
	BackToManageUsersMenue();
}

void FindUserScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Find Users Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	FindManyUsers();
}

void WorkingInMainMenue() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	vector<stUser> vUsers = StoreFileInUsersVector();
	stUser User;

		enMainMenuAction MainMenueAction;
		MainMenueShape();
		cout << "Choose What do you want to do from [ 1 to 8 ] " << endl;
		MainMenueAction = enMainMenuAction(EnterNumberWithCondition(8));
		switch (MainMenueAction)
		{
		case ListClients:
			system("cls");
			PrintAllClientsData();
			break;
		case NewClient:
			system("cls");
			EnterManyClientsData();
			break;
		case DeleteClient:
			system("cls");
			DeleteClientScreen();
			break;
		case UpdateClient:
			system("cls");
		 UpdateClientScreen();
			break;
		case FindClient:
			system("cls");
			FindClientScreen();
			break;
		case TransactionMenue:
			 WorkingWithTransactionMenue();
			break;
		case ManageUsers:
			WorkingInManageUsersMenue();
			break;
		case LoginPage:
			LoginInterface();
			break;
		}
	
}

void WorkingWithTransactionMenue() {
	if (!HavePermission(pTransactions)) {
		AccessDenied();
		
	}
	enTransatcionMenueAction TransactionMenueAction;
	TransactionMenueShape();
	cout << "Choose What do you want to do from [ 1 to 4 ] " << endl;
	TransactionMenueAction = enTransatcionMenueAction(EnterNumberWithCondition(4));
	switch (TransactionMenueAction)
	{
	case Deposit:
		system("cls");
		DepositScreen();
		break;
	case WithDrawl:
		system("cls");
		WithDrawlScreen();
		break;
	case TotalBalances:
		system("cls");
		TotalBalancesScreen();
		break;
	case MainMenue:
		WorkingInMainMenue();
		break;

	}
}

void WorkingInManageUsersMenue() {
	if (!HavePermission(pManageUsers)) {
		AccessDenied();
	}
	system("cls");
	vector<stClientData> vClients = StoreFileInClientDataVector();
	vector<stUser> vUsers = StoreFileInUsersVector();
	ManageUserMenueShape();
	cout << "\nChoose What do you want to do from [ 1 to 6 ] " << endl;
	enManageUsersMenueAction ManageUserMenueAction = (enManageUsersMenueAction)EnterNumberWithCondition(6);
	switch (ManageUserMenueAction)
	{
	case ListUsers:
		PrintAllUsersScreen();
		break;
	case NewUser:
		AddNewUserScreen();
		break;
	case DeleteUser:
		DeleteUsersScreen();
		break;
	case UpdateUser:
		UpdateUsersScreen();
		break;
	case FindUser:
		FindUserScreen();
		break;
	case MainMenue1:
		WorkingInMainMenue();
		break;

	}
}

int main() {
	
	LoginInterface();

	return 0;
}