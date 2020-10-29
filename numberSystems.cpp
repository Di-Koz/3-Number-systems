#include <iostream>
#include <ctime>
#include <string>
//#include <cmath>
#include <iomanip>
//русский текст

using namespace std;

unsigned long long pow(int ch, int stepen);
//1
long long fibRec(int ch);
long long fib(int ch);
long long fibBinne(int ch);
//2
long intTo10SS(string userCh, int userSS);
double doubleTo10SS(string userCh, int userSS);
string int10ToSS(long userCh, int userSS);
string double10ToSS(double userCh, int userSS, int kolvoZifr);
string perevod(string ch, int nachSS, int konachSS);
bool checkZifry(string ch, int SS);
bool checkZnam(long long ch, int SS);

int main() {
	//1
	//int a{ 50 };
	//int timeStart = clock();
	////cout << fib(a) << endl;
	//cout << fibBinne(a) << endl;
	//int timeEnd = clock();
	//cout << timeEnd - timeStart << "ms";
	////2
	string str{ "FDEH.123" };
	int firstSS{ 35 }, secondSS{ 5 };
	//cin >> str;
	
	if (checkZifry(str, firstSS)) {
		cout << perevod(str, firstSS, secondSS);
	}
	else {
		cerr << "error";
	}
}
//1
long long fibRec(int ch) {
	if (ch == 1 || ch == 2) {
		return 1;
	}
	else {
		return fibRec(ch - 1) + fibRec(ch - 2);
	}
}

long long fib(int ch) {
	long long ch1{ 1 }, ch2{ 1 };
	for (int i{2}; i < ch; ++i) {
		i % 2 == 0 ? ch1 += ch2 : ch2 += ch1;
	}

	return ch % 2 == 1 ? ch1 : ch2;
}

long long fibBinne(int ch) {
	double fi{ (1 + sqrt(5)) / 2 }, fi2{ (1 - sqrt(5)) / 2 };
	//*\\
	//çäåñü íóæåí èìåííî double, ïîòîìó ÷òî çíà÷åíèå âûðàæåíèÿ áóäåò
	//âåùåñòâåííûì ÷èñëîì, îíî íå ïðåîáðàçóåòñÿ ê èíòó. Ïîãóãëèâ, ÿ íàøëà
	//ïðèîðèòåò òèïîâ îïåðàíäîâ, è âñå âñòàëî íà ñâîè ìåñòà. Ñðåäè âñÿêèõ 
	//double, float è ñàìûõ ðàçíûõ int, double íà âòîðîì ìåñòå, 
	//çíà÷èò â ñêîáêå ñíà÷àëà îí ïåðâîå ñëàãàåìîå ïðåîáðàçóåò â double 
	//(int + double), à ïîòîì îí äåëèòåëü ïðåîáðàçóåò â double (double / int)
	return (pow(fi, ch) - pow(fi2, ch)) / sqrt(5);
}
//2
long intTo10SS(string userCh, int userSS) {
	int newCh{ 0 };
	for (int i{ 0 }; i < userCh.size(); ++i) {
		if (userCh[i] <= 57) {
			newCh = newCh * userSS + (int(userCh[i]) - '0');
		}
		else {
			newCh = newCh * userSS + ((int(userCh[i]) - '0') - 7);
		}
	}
	return newCh;
}

double doubleTo10SS(string userCh, int userSS) {
	double newCh{ 0 };
	//double newCh{ int(userCh[2] - '0') / double(userSS) + (int(userCh[3]) - '0') };
	double stepen = 1 / double(userSS);

	for (int i{2}; i <= userCh.size() - 1; ++i) {
		if (userCh[i] <= 57) {
			newCh += (int(userCh[i]) - '0') * stepen;
		}
		else {
			newCh += (int(toupper((userCh[i])) - '0') - 7) * stepen;
		}
		stepen /= userSS;
	}
	//*\\
	//ÿ âåäü ïîíèìàþ, ÷òî íå âñå äðîáíûå ÷èñëà ìîæíî ïåðåâåñòè â 10 ññ,
	//ïîýòîìó òå, ÷òî íåëüçÿ, ÿ îáðåçàþ äî 15 öèôðû ïîñëå çàïÿòîé
	//ïîòîìó ÷òî ïîñëå 15 óæå èäåò ïîãðåøíîñòü
	if (!checkZnam(userSS, 10)) {
		newCh = trunc(newCh * pow(10, 15)) / pow(10, 15);
	}
	//*\\
	//à äàëüøå íå î÷åíü óäà÷íàÿ ïîïûòêà ðåàëèçîâàòü ìåòîä Ãîðíåðà äëÿ äðîáåé

	/*for (int i{ 4 }; i < userCh.size(); ++i) {
		if (userCh[i] <= 57) {
			newCh = newCh / double(userSS) + int(userCh[i] - '0');
		}
		else {
			newCh = newCh / double(userSS) + ((int(userCh[i]) - '0') - 7);
		}
	}

	if (userCh[userCh.size() - 1] != '0') {
		newCh /= userSS;
	}*/
	return newCh;
}


string int10ToSS(long userCh, int userSS) {
	string newCh = "";

	do {
		if (userCh % userSS < 10) {
			newCh += to_string(userCh % userSS);
		}
		else {
			newCh += char(userCh % userSS + 7 + '0');
		}
		userCh /= userSS;
	} while (userCh != 0);
	reverse(newCh.begin(), newCh.end());
	return newCh;
}

string double10ToSS(double userCh, int userSS, int kolvoZifr) {
	string newCh = { "0." };

	do {
		userCh *= double(userSS);
		int userCh2{ 0 };

		if ((round(userCh) >= userCh) 
			&& (round(userCh) - userCh > 0.00001)) {
			userCh2 = int(userCh);
		}
		else {
			userCh2 = round(userCh);
		}
		
		if (trunc(userCh) < 10) {
			newCh += to_string(userCh2);
		}
		else {
			newCh += char(int(userCh2 + 7 + '0'));
		}

		userCh -= userCh2;
		--kolvoZifr;
	} while ((to_string(userCh) != "0.000000") && (userCh > 0) && (kolvoZifr > 0));
	return newCh;
}

string perevod(string ch, int nachSS, int konechSS) {
	unsigned int dlina{ ch.size() };	
	int indTochka{ 0 };

	for (int i{0}; i < dlina; ++i) {
		if (ch[i] == '.') {
			indTochka = i;
			break;
		}
	}

	string zeloe{ "" }, drob{"0."};

	for (int i{0}; i < indTochka; ++i) {
		zeloe += ch[i];
	}

	for (int i{ indTochka + 1 }; i < dlina; ++i) {
		drob += ch[i];
	}

	long zeloe10SS = intTo10SS(zeloe, nachSS);
	string newZeloe = int10ToSS(zeloe10SS, konechSS);
	double drob10SS = doubleTo10SS(drob, nachSS);
	//*\\
	//êîãäà ÿ ïîëó÷èëà äðîáü â 10 ññ, ìíå íóæíî ïðîâåðèòü åå íà êîíå÷íîñòü
	double drob10SS2 = drob10SS;
	int kolvoDoubleZifr{ 0 };
	//*\\
	//íî äëÿ ýòîãî íóæíî ñíà÷àëà ïîëó÷èòü åå ÷èñëèòåëü è çíàìåíàòåëü
	//÷èñëèòåëü ÿ ïîëó÷ó, êîãäà âñå öèôðû èç äðîáíîé ÷àñòè ïåðåâåäó â öåëóþ,
	//à çíàìåíàòåëü ýòî 10 â ñòåïåíè, ðàâíîé êîëè÷åñòâó ðàç, ñêîëüêî íóæíî
	//äîìíîæèòü íà 10, ÷òîáû ïåðåâåñòè âñå â öåëóþ ÷àñòü
	while (drob10SS2 - trunc(drob10SS2)) {
		drob10SS2 *= 10;
		++kolvoDoubleZifr;
	}

	long long chislitel = drob10SS2;
	long long znamenatel = pow(10, kolvoDoubleZifr);
	//*\\
	//çàòåì ñîêðàùàþ äðîáü íà 2 èëè 5 (äåëèòåëè 10), ïîêà ýòî âîçìîæíî
	while ((chislitel % 5 == 0 && znamenatel % 5 == 0) 
		|| (chislitel % 2 == 0 && znamenatel % 2 == 0)) {
		if (chislitel % 2 == 0 && znamenatel % 2 == 0) {
			chislitel /= 2;
			znamenatel /= 2;
		}
		else if (chislitel % 5 == 0 && znamenatel % 5 == 0) {
			chislitel /= 5;
			znamenatel /= 5;
		}
	}
	//*\\
	//äàëüøå ïðîâåðÿþ, êîíå÷íà ëè ïðåäñòàâèìà äðîáü, è â çàâèñèìîñòè îò 
	//ýòîãî áóäó âûâîäèòü îïðåäåëåííîå êîë-âî (output) öèôð ïîñëå çàïÿòîé
	//åñëè ïðåäñòàâèìà, òî î÷ áîëüøîå çíà÷åíèå ïåðåìåííîé, ÷òîáû öèêë
	//â ôóíêöèè ïðîñòî òàê íå ïðåðâàëñÿ, åñëè íåò, òî òîëüêî 15 öèôð
	int output{ 0 };
	if (checkZnam(znamenatel, konechSS)){
		output = INT16_MAX;
	}
	else {
		output = 15;
	}
	string newDrob = double10ToSS(drob10SS, konechSS, output);
	newDrob.erase(0, 1);

	return newZeloe + newDrob;
}

unsigned long long pow(int ch, int stepen) {
	if (stepen == 0) {
		return 1;
	}
	else {
		unsigned long long newCh{ 1 };
		for (int i{1}; i <= stepen; ++i) {
			newCh *= ch;
		}
		return newCh;
	}
}

bool checkZifry(string ch, int SS) {
	for (int i{0}; i < ch.size(); ++i) {
		if (ch[i] <= 57) {
			if ((ch[i] - '0') >= SS) {
				return false;
			}
		}
		else {
			if ((ch[i] - '0' - 7) >= SS) {
				return false;
			}
		}
		
	}

	return true;
}

bool checkZnam(long long ch, int SS) {
	int del = 2, ind{ 0 }, lenghtCh{ 0 }, lenghtSS{0}, 
		mnozCh[100]{ 0 }, mnozSS[100]{ 0 };
	//*\\
	//çàïèñûâàþ âñå äåëèòåëè ÷èñëà
	while (ch > 1) {
		while (ch % del == 0)
		{
			mnozCh[ind] = del;
			++ind;
			++lenghtCh;
			ch = ch / del;
		}
		del++;
	}
	del = 2;
	ind = 0;
	//*\\
	//çàïèñûâàþ âñå äåëèòåëè ññ
	while (SS > 1) {
		while (SS % del == 0)
		{
			mnozSS[ind] = del;
			++ind;
			++lenghtSS;
			SS = SS / del;
		}
		del++;
	}

	int lenghtMasCh = lenghtCh;
	int lenghtMasSS = lenghtSS;
	//*\\
	//îáíóëÿþ âñå ïîâòîðÿþùèå äåëèòåëè ÷èñëà
	for (int i{0}; i < lenghtCh - 1; ++i) {
		for (int j{i + 1}; j < lenghtCh; ++j) {
			if (mnozCh[i] == mnozCh[j] && mnozCh[i] != 0) {
				mnozCh[j] = 0;
				--lenghtMasCh;
			}
		}
	}
	//*\\
	//îáíóëÿþ âñå ïîâòîðÿþùèå äåëèòåëè ññ
	for (int i{ 0 }; i < lenghtSS - 1; ++i) {
		for (int j{ i + 1 }; j < lenghtSS; ++j) {
			if (mnozSS[i] == mnozSS[j] && mnozSS[i] != 0) {
				mnozSS[j] = 0;
				--lenghtMasSS;
			}
		}
	}

	int* masMnozhCh = new int[lenghtMasCh];
	bool* checkMnozhCh = new bool[lenghtMasCh] {false};
	int* masMnozhSS = new int[lenghtMasSS];
	ind = 0;
	//*\\
	//çàïèñûâàþ íåïîâòîðÿþùèåñÿ ìíîæèòåëè ÷èñëà â íîâûé ìàññèâ
	for (int i{ 0 }; i < lenghtCh; ++i) {
		if (mnozCh[i] != 0) {
			masMnozhCh[ind] = mnozCh[i];
			++ind;
		}
	}
	ind = 0;
	//*\\
	//çàïèñûâàþ íåïîâòîðÿþùèåñÿ ìíîæèòåëè ññ â íîâûé ìàññèâ
	for (int i{ 0 }; i < lenghtSS; ++i) {
		if (mnozSS[i] != 0) {
			masMnozhSS[ind] = mnozSS[i];
			++ind;
		}
	}

	ind = 0;
	//*\\
	//ïðîâåðÿþ âõîäèò ëè êàæäûé ìíîæèòåëü ÷èñëà â ìàññèâ ñ ìíîæèòåëÿìè ññ
	mainZicl:while (ind < lenghtMasCh) {
		for (int j{0}; j < lenghtMasSS; ++j) {
			if (masMnozhCh[ind] == masMnozhSS[j]) {
				checkMnozhCh[ind] = true;
				++ind;
				goto mainZicl;
			}
		}
		++ind;
	}
	//*\\
	//ïðîâåðêà áóëåâîãî ìàññèâà
	for (int i{0}; i < lenghtMasCh; ++i) {
		if (!checkMnozhCh[i]) {
			return false;
		}
	}
	return true;
}
