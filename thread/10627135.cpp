# include <iostream>
# include <stdio.h>
# include <vector>
# include <ctype.h>
# include <string> 
# include <cstring>
# include <fstream>
# include <thread>
# include <time.h>

using namespace std;

struct Data {
	long dataNum;
};

vector <Data> StayData;
vector <long> num;
vector <long> num2;
vector <long> numS;
vector <vector <long>> everyThr;
//vector<long> leftSubArray;
//vector<long> rightSubArray;
vector <thread> vecOfThreads;
string whatMission ;

bool getFile(string fileName ) {
	ifstream fin;
	char ch;
	string stay;
	string stay2;
	long aNum = 0;
	vector <string> data;

	fin.open(fileName);

	if (!fin) {
		return false;
		//cout << "�ɮ׵L�k�}�ҩΤ��s�b!\n";
	} // if
	else {

		getline(fin, stay);
		whatMission = stay;
		//cout << whatMission;

		while (fin.peek() != EOF ) {
			getline( fin, stay );
			for (int i = 0; i < stay.length(); i++) {
				if ( stay[i] != ' ' && i < stay.length() ) {
					stay2 = stay2 + stay[i];
				} // if
				else if ( stay2 != "\0" ) {
					//cout << stay2 << " ";
					aNum = stoi(stay2);
					num.push_back(aNum);
					stay2 = "\0";
				} // else
			} // for

			if ( stay2 != "\0" ) {
				//cout << stay2 << " ";
				aNum = stoi(stay2);
				num.push_back(aNum);
				stay2 = "\0";
			} // if
			/*
			fin >> aNum;
			//cout << stay << " ";
			//aNum = stoi(stay);
			num.push_back(aNum);
			*/
		} // while

		return true;
	} // else 

} // getFile ()

void writeFile(string fileName, double time) {
	ofstream fout;
	string outFileName;

	for ( int i = 0 ; i < fileName.size() ; i++ ) {
		if ( fileName[i] == '.' ) {
			outFileName = outFileName + "_mission" +  whatMission; 
			outFileName = outFileName + "_output.";
		} // if
		else {
			outFileName = outFileName + fileName[i];
		} // else
	} // for

	cout << outFileName << "\n";

	fout.open(outFileName);
	fout << "�Ƨ� : \n";

	if (whatMission == "1") {

		for (int i = 0; i < numS.size() ; i++) {
			fout << numS[i] << " ";
		} // for

		fout << "\n";

		fout << "����ɶ� : " << time;

	} // if
	else if (whatMission == "2") {
		for (int i = 0; i < everyThr[0].size(); i++) {
			fout << everyThr[0][i] << " ";
		} // for

		fout << "\n";

		fout << "����ɶ� : " << time;
	} // else if
	else if (whatMission == "4") {
		for (int i = 0; i < everyThr[0].size(); i++) {
			fout << everyThr[0][i] << " ";
		} // for

		fout << "\n";

		fout << "����ɶ� : " << time;
	} // else
	/*
	for (int i = 0; i < ; i++) {

	} // for
	*/
} // writeFile
//*/

void Merge2(int dest, int first, int second , int x) { // everyThr[1]�ؼ� , ��J everyThr[3], everyThr[4]

	int firVec = 0, secVec = 0;
	int howLong = everyThr[first].size() + everyThr[second].size();
	long stay = 0;
	vector <long> newThr;

	everyThr[first].push_back(numeric_limits<long>::max());
	everyThr[second].push_back(numeric_limits<long>::max());

	for (int i = 0; i < howLong ; i++) {
		if ( everyThr[first][firVec] < everyThr[second][secVec]) {
			newThr.push_back(everyThr[first][firVec]);
			firVec++;
		} // if 
		else {
			newThr.push_back(everyThr[second][secVec]);
			secVec++;			
		}
	} // for

	everyThr[dest].swap(newThr); // 0,1=> 0  2, 3=> 1

	if ( x % 2 == 1 && first + 2 == x - 1 ) {
		everyThr[dest + 1].swap(everyThr[x - 1]); // �N�̫�@����J�κ��C��
	} // if
} // Merge2()

void BubbleSort(vector <long>& numS) {
	Data stay;
	long stay2;

	for (int i = 0; i < numS.size() - 1; i++) {
		for (int j = 0; j < numS.size() - 1; j++) {
			if (numS[j] > numS[j + 1]) {
				stay2 = numS[j];
				numS[j] = numS[j + 1];
				numS[j + 1] = stay2;
			} // if
		} // for
	} // for

} // bubbleSort ()

void BubbleSortForThread( int k ) {
	long stay;

	for (int i = 0; i < everyThr[k].size() - 1; i++) {
		for (int j = 0; j < everyThr[k].size() - 1; j++) {
			if ( everyThr[k][j] > everyThr[k][j + 1]) {
				stay = everyThr[k][j];
				everyThr[k][j] = everyThr[k][j + 1];
				everyThr[k][j + 1] = stay;
			} // if
		} // for
	} // for
	
} // bubbleSort ()

void mission1(vector<long>& numS, string fileName) {

	double start, end;
	double time;

	start = clock();
	BubbleSort(numS);
	end = clock();

	time = end - start;

	for (int i = 0; i < numS.size(); i++) {
		cout << numS[i] << " ";
	} // for

	//cout << "�{������Ҫ�O�G" << (double)clock() << " mS\n";
	cout << endl << "�i��B��Ҫ�O���ɶ��G" << time << " mS" << endl;

	writeFile(fileName, time);

} // mission1

void mission2( int k, string fileName ) {
	vector <thread> thrs;
	vector <long> aThr;
	
	int aMerg = (num.size()) / k; //�@��merge�n�h�ָ�� 
	int last = (num.size()) % k;
	int x = 0;
	long stay = 0;
	bool push = false;
	bool odd = false;
	double start, end;
	double time;

	// ����K��vector
	start = clock();

	for (int i = 0; i < k ; i++) {
		for ( int j = 0; x < num.size() && j < aMerg; j++, x++) {
			stay = num[x];
			aThr.push_back(stay);
			//cout << stay << " ";

			if (j == aMerg) {
				push = true;
				//cout << "j : " << j << "\n";
				everyThr.push_back(aThr);
				vector<long>().swap(aThr);
			} // if
		} // for

		if ( !push && x < num.size() && i != k - 1) {
			//cout << "end line \n";
			everyThr.push_back(aThr);
			vector<long>().swap(aThr);
			push = true;
		} // if

		push = false;
	} // for 

	if ( !push && x <= num.size()) {
		while (x < num.size()) {
			stay = num[x];
			aThr.push_back(stay);
			//cout << stay << " ";
			x++;
		} // while

		if (!push) {
			//cout << "end line \n";
			everyThr.push_back(aThr);
			vector<long>().swap(aThr);
			push = true;
		} // if

	} // if
	
	for (int i = 0; i < k ; i ++ ) {
		thrs.push_back( thread( BubbleSortForThread, i) );
	} // for

	for (int i = 0; i < k ; i++) {
		thrs[i].join();
	} // for
	
	vector<thread>().swap(thrs); // �Nthread vector�M��
	
	//Merge Sort k - 1
	// K�_���B�z �_:�̫�@�ӥ����B�z�A�̫�[�W  ��:�����B��(k/2)
	int i = 0, j = 0  ;
	x = k;
	int up = k - 1; // �W������
	
	while( up != 0 ) {
		while ( i < ( x / 2 ) && j < x ) { // 5/2 = 2 
			thrs.push_back( thread( Merge2, i, j, j + 1, x ) ); // �I�sthread
			i++;
			j = j + 2;
			up--; // �I�sthread�N-1
		} // while

		for (int i = 0; i < thrs.size() ; i++) {
			thrs[i].join();
		} // for

		if ( x % 2 == 1 ) {
			x = (x / 2) + 1; // 5=>3 7=>5
		} // if
		else {
			x = x / 2;
		} // else

		i = 0;
		j = 0;
		vector<thread>().swap(thrs); // �Nthread vector�M��

	} // while	
	
	end = clock();

	time = end - start;
	
	for (int i = 0; i < everyThr[0].size(); i++) {
		cout << everyThr[0][i] << " " ;
	} // for
	
	cout << endl << "�i��B��Ҫ�O���ɶ��G" << time << " mS" << endl;

	writeFile(fileName, time);

} // mission2

void mission4( int k, string fileName) {

	vector <long> aThr;
	int aMerg = (num.size()) / k; //�@��merge�n�h�ָ�� 
	int last = (num.size()) % k;
	int x = 0;
	long stay = 0;
	bool push = false;
	bool odd = false;

	double start, end;
	double time;

	start = clock();

	// ����K��vector 
	for (int i = 0; i < k; i++) {
		for (int j = 0; x < num.size() && j < aMerg; j++, x++) {
			stay = num[x];
			aThr.push_back(stay);
			//cout << stay << " ";

			if (j == aMerg) {
				push = true;
				//cout << "j : " << j << "\n";
				everyThr.push_back(aThr);
				vector<long>().swap(aThr);
			} // if
		} // for

		if (!push && x < num.size() && i != k - 1) {
			//cout << "end line \n";
			everyThr.push_back(aThr);
			vector<long>().swap(aThr);
			push = true;
		} // if

		push = false;
	} // for 

	if (!push && x <= num.size()) {
		while (x < num.size()) {
			stay = num[x];
			aThr.push_back(stay);
			//cout << stay << " ";
			x++;
		} // while

		if (!push) {
			//cout << "end line \n";
			everyThr.push_back(aThr);
			vector<long>().swap(aThr);
			push = true;
		} // if

	} // if

	for (int i = 0 ; i < k ; i++ ) {
		BubbleSortForThread( i );
	} // for

	for (int i = 0; i < everyThr[0].size(); i++) {
		cout << everyThr[0][i] << " ";
	} // for

	cout << endl;

	//Merge Sort k - 1
	// K�_���B�z �_:�̫�@�ӥ����B�z�A�̫�[�W  ��:�����B��(k/2)
	int i = 0, j = 0;
	x = k;
	int up = k - 1; // �W������

	while (up != 0) {
		while (i < (x / 2) && j < x) { // 5/2 = 2 
			Merge2( i, j, j + 1, x); // �I�sthread
			i++;
			j = j + 2;
			up--; // �I�sthread�N-1
		} // while

		if (x % 2 == 1) {
			x = (x / 2) + 1; // 5=>3 7=>5
		} // if
		else {
			x = x / 2;
		} // else

		i = 0;
		j = 0;
	} // while	

	end = clock();

	time = end - start;
	
	for (int i = 0; i < everyThr[0].size(); i++) {
		cout << everyThr[0][i] << " ";
	} // for
	
	cout << endl << "�i��B��Ҫ�O���ɶ��G" << time << " mS" << endl;

	writeFile(fileName, time);

} // mission4

int main() {

	int k = 0; // K�Ӱ���� 
	bool hasfile ;
	bool leave = false;
	int aNum = 0;
	string fileName;
	string stay;
	char c;

	while (!leave) {
		cout << "�п�J�ɮצW��,��J0���} : ";
		cin >> fileName;

		if (fileName == "0") {
			leave = true;
		} // if
		else {
			hasfile = getFile(fileName);
		} // else
		
		if (!hasfile) {
			cout << "�ɮ׵L�k�}�ҩΤ��s�b!\n";
		} // if
		else {
			if (whatMission == "1") {
				
				for (int i = 0; i < num.size(); i++) {
					numS.push_back(num[i]);
				} // for

				mission1(numS, fileName);

			} // else  if
			else if (whatMission == "2") {
				cout << "�n�N��Ƥ�?�� :";
				cin >> k;
				//vector <vector <long>> everyThr;  // �ŧik��vector�A�C�@�ӳ��i�H�slong
				mission2(k, fileName); // �B�z��� 

				vector <vector <long>>().swap(everyThr);

			} // else
			else if (whatMission == "4") {
				cout << "�n�N��Ƥ�?�� :";
				cin >> k;
				mission4(k, fileName);
				vector <vector <long>>().swap(everyThr);
			} // else
			else {
				cout << "���s�b�Ӻإ��ȡA�Э��s�]�w�ɮ�!\n";
			} // else
		} // else

		hasfile = false;
		vector<long>().swap(num);
		vector<long>().swap(num2);
		vector<long>().swap(numS);
	} // while

	for (int k = 0; k < num.size(); k++) {
		cout << num[k] << " ";
	} // for
	cout << "\n";
	
	return 0;
} // main
