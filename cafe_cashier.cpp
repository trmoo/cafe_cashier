#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Cafe {
public:
	int Order(ofstream &fout); // 주문 받기를 시작하는 함수
	void showMenu(); // 메뉴를 보여주는 함수
	void printReceipt(int t, int d); // 영수증 출력을 담당하는 함수
	void saveCurrentTime(ofstream &fout); // 현재 시간을 파일을 저장할 때 쓰는 함수
};

void Cafe::showMenu() {
	cout << "---<< Welcome to C++ Cafe >>---" << endl;
	cout << "1. Tea" << endl;
	cout << "2. Coffee" << endl;
	cout << "3. Cake" << endl;
	cout << "-------------------------------" << endl;
	cout << "Select Menu : ";
}

void Cafe::saveCurrentTime(ofstream &fout) {
	int totalSeconds = time(0); // 1970년 1월 1일 0시부터 경과한 초
	int currentSecond = totalSeconds % 60; // 현재 시각의 초 (GMT)
	int totalMinutes = totalSeconds / 60; // 1970년 1월 1일 0시부터 경과한 분
	int currentMinute = totalMinutes % 60; // 현재 시각의 분 (GMT)
	long totalHours = totalMinutes / 60; // 1970년 1월 1일 0시부터 경과한 시
	int currentHour = (int)(totalHours % 24); // 현재 시각의 시 (GMT)

	fout << "Current time is " << currentHour + 9 << ":"
		<< currentMinute << ":" << currentSecond << endl; // 현재 시각을 파일에 출력 (한국시각)
}

void Cafe::printReceipt(int total, int date) {
	while (1) {
		try {
			char asw;
			cout << "영수증을 받으시겠습니까? (y/n) : ";
			cin >> asw;

			switch (asw) {
			case 'n': cout << "이용해주셔서 감사합니다." << endl; break;
			case 'y': {
				ofstream receipt("영수증.txt"); // 영수증을 출력할 파일을 텍스트모드로 생성
				receipt << "C++ Cafe" << endl; // 가게 이름 저장
				receipt << "날짜:" << date << endl; // 오늘날짜 저장
				receipt << "시각: ";
				saveCurrentTime(receipt); // 현재시각 저장
				receipt << endl;
				receipt << "총 금액:" << total << endl; // 결제금액 저장
				receipt.close();

				cout << "영수증이 발급되었습니다." << endl;
				cout << "파일을 확인해 보십시오." << endl;
				cout << "영수증 파일이 업데이트 되면 이전 정보는 지워집니다." << endl;
				break;
			}
			default: throw asw; // 잘못된 입력에 대한 예외처리
			}
		}
		catch (char asw) {
			cout << asw << ": 잘못된 입력" << endl;
			continue;
		}
		break;
	}
}

////////////////////////////////////////////////

class Food : public Cafe {
protected:
	int subMenu, price;
public:
	Food(int price = 0) { // Food의 생성자는 price를 초기화
		this->price = price;
	}

	void operator+ (int price) { // 기본 가격에 price만큼 더함
		cout << this->price << " + " << price << endl;
		(this->price += price);
	}

	int getPrice() {
		return price;
	}
};


///////////////////////////////////////////////

class Tea : public Food {
	int IceHot;
	int size;
public:
	Tea() : Food(2500) {}
	void setSubmenu(ofstream &fout);
	void setHotIce(ofstream &fout);
	void setSize(ofstream &fout);
};

void Tea::setSubmenu(ofstream &fout) {
	while (1) {
		try {
			cout << "<Tea Menu>----------" << endl;
			cout << "1. Green Tea" << endl;
			cout << "2. Lemon Tea" << endl;
			cout << "3. Chai Tea" << endl;
			cout << "4. Yuja Tea" << endl;
			cout << "5. Mint Tea" << endl;
			cout << "--------------------" << endl;
			cout << "Select Tea : ";
			cin >> subMenu;
			switch (subMenu) { // subMenu 정보를 파일에 저장
			case 1: fout << " -  Green"; break;
			case 2: fout << " -  Lemon"; break;
			case 3: fout << " -  Chai"; break;
			case 4: fout << " -  Yuja"; break;
			case 5: fout << " -  Mint"; break;
			default: throw subMenu; // 잘못된 입력에 대한 예외 처리
			}
			break;
		}
		catch (int x) {
			cout << x << " : 잘못된 입력" << endl;
		}
	}
}

void Tea::setHotIce(ofstream &fout) {
	while (1) {
		try {
			cout << "-----(Hot/Ice)-----" << endl;
			cout << "1. Hot" << endl;
			cout << "2. Ice (+500)" << endl;
			cout << "-------------------" << endl;
			cout << "Select Hot/Ice : ";
			cin >> IceHot;
			switch (IceHot) { // IceHot 정보를 파일에 저장
			case 1: fout << " - Hot"; break;
			case 2: fout << " - Ice"; (*this) + 500; break;
			default: throw IceHot; // 잘못된 입력에 대한 예외처리
			}
			cout << "Price = " << getPrice() << endl;
			break;
		}
		catch (int x) {
			cout << x << ": 잘못된 입력" << endl;
		}
	}
}

void Tea::setSize(ofstream &fout) {
	while (1) {
		try {
			cout << "------(Size)-------" << endl;
			cout << "1. Short" << endl;
			cout << "2. Venti (+800)" << endl;
			cout << "-------------------" << endl;
			cout << "Select Size : ";
			cin >> size;
			switch (size) { // size 정보를 파일에 저장
			case 1: fout << " - Short"; break;
			case 2: fout << " - Venti"; (*this) + 800; break;
			default: throw size; // 잘못된 입력에 대한 예외 처리
			}
			cout << "Price = " << getPrice() << endl;
			break;
		}
		catch (int x) {
			cout << x << " : 잘못된 입력" << endl;
		}
	}
}

////////////////////////////////////////////

class Coffee : public Food {
	int IceHot;
	int size;
public:
	Coffee() : Food(2000) {}
	void setSubmenu(ofstream &fout);
	void setHotIce(ofstream &fout);
	void setSize(ofstream &fout);
};

void Coffee::setSubmenu(ofstream &fout) {
	while (1) {
		try {
			cout << "<Coffee Menu>-------" << endl;
			cout << "1. Americano" << endl;
			cout << "2. Hazlenut Latte" << endl;
			cout << "3. Espresso" << endl;
			cout << "4. Dolce Latte" << endl;
			cout << "5. Coffee Mocha" << endl;
			cout << "--------------------" << endl;
			cout << "Select Coffee : ";
			cin >> subMenu;
			switch (subMenu) {
			case 1: fout << " - Americano"; break;
			case 2: fout << " - Hazlenut Latte"; break;
			case 3: fout << " - Espresso"; break;
			case 4: fout << " - Dolce Latte"; break;
			case 5: fout << " - Coffee Mocha"; break;
			default: throw subMenu;
			}
			break;
		}
		catch (int x) {
			cout << x << " : 잘못된 입력" << endl;
		}
	}
}

void Coffee::setHotIce(ofstream &fout) {
	while (1) {
		try {
			cout << "-----(Hot/Ice)-----" << endl;
			cout << "1. Hot" << endl;
			cout << "2. Ice (+600)" << endl;
			cout << "-------------------" << endl;
			cout << "Select Hot/Ice : ";
			cin >> IceHot;
			switch (IceHot) {
			case 1: fout << " - Hot"; break;
			case 2: fout << " - Ice"; (*this) + 600; break;
			default: throw IceHot;
			}
			cout << "Price = " << getPrice() << endl;
			break;
		}
		catch (int x) {
			cout << x << " : 잘못된 입력" << endl;
		}
	}
}

void Coffee::setSize(ofstream &fout) {
	while (1) {
		try {
			cout << "------(Size)-------" << endl;
			cout << "1. Short" << endl;
			cout << "2. Venti (+500)" << endl;
			cout << "-------------------" << endl;
			cout << "Select Size : ";
			cin >> size;
			switch (size) {
			case 1: fout << " - Short"; break;
			case 2: fout << " - Venti"; (*this) + 500; break;
			default: throw size;
			}
			cout << "Price = " << getPrice() << endl;
			break;
		}
		catch (int x) {
			cout << x << " : 잘못된 입력" << endl;
		}
	}
}

////////////////////////////////////////

class Cake : public Food {
public:
	Cake() : Food(5000) {}
	void setSubmenu(ofstream &fout);
};

void Cake::setSubmenu(ofstream &fout) {
	while (1) {
		try {
			cout << "<Cake Menu>---------" << endl;
			cout << "1. Chocolate Cake" << endl;
			cout << "2. Cheese Cake" << endl;
			cout << "3. Red Velvet Cake" << endl;
			cout << "4. Sweet Potato Cake" << endl;
			cout << "5. Carrot Cake" << endl;
			cout << "--------------------" << endl;
			cout << "Select Cake : ";
			cin >> subMenu;
			switch (subMenu) {
			case 1: fout << " - Chocolate Cake"; break;
			case 2: fout << " - Cheese Cake"; break;
			case 3: fout << " - Red Velvet Cake"; break;
			case 4: fout << " - Sweet Potato Cake"; break;
			case 5: fout << " - Carrot Cake"; break;
			default: throw subMenu;
			}
			break;
		}
		catch (int x) {
			cout << x << ": 잘못된 입력" << endl;
		}
	}
}

///////////////////////////////////////////

int Cafe::Order(ofstream &fout) {
	int total = 0; // 현재 손님이 결제해야할 총 액수
	while (1) {
		try {
			int menu;
			showMenu();
			cin >> menu;

			switch (menu) {
			case 1:
			{
				fout << "Tea";
				Tea t;
				cout << "Tea's default price = " << t.getPrice() << endl;
				t.setSubmenu(fout);
				t.setHotIce(fout);
				t.setSize(fout);
				fout << " = " << t.getPrice() << endl; // 옵션까지 합한 액수
				total += t.getPrice();
				break;
			}
			case 2:
			{
				fout << "Coffee";
				Coffee cf;
				cout << "Coffee default price = " << cf.getPrice() << endl;
				cf.setSubmenu(fout);
				cf.setHotIce(fout);
				cf.setSize(fout);
				fout << " = " << cf.getPrice() << endl;
				total += cf.getPrice();
				break;
			}
			case 3:
			{
				fout << "Cake";
				Cake ck;
				cout << "Cake' default price :" << ck.getPrice() << endl;
				ck.setSubmenu(fout);
				fout << " = " << ck.getPrice() << endl;
				total += ck.getPrice();
				break;
			}
			default: throw menu;
			}
		}
		catch (int menu) {
			cout << menu << " : 잘못된 입력" << endl;
			continue; // 메뉴를 다시 불러온다.
		}


		while (1) {
			try {
				cout << "Do you want anything else? (y/n) ";
				char asw;
				cin >> asw;
				switch (asw) {
				case 'n':
					cout << "Total price: " << total << endl;
					return total;
				case 'y': break;
				default: throw asw;
				}
				break;
			}
			catch (char asw) {
				cout << asw << " : 잘못된 입력" << endl;
				continue; // 더 주문할 것이 있는지 다시 질의한다.
			}
		}
	}
	return total;
}


int main() {
	int sale = 0; // 오늘 가게 수입
	int countCustomer = 0; // 오늘 가게 손님 수

	while (1) {
		try {
			char asw;
			cout << "C++ Cafe Program" << endl;
			cout << "오늘 영업을 시작하시겠습니까? (y/n) : ";
			cin >> asw;
			switch (asw) {
			case 'n':
				cout << "프로그램을 끝냅니다. " << endl;
				return 0;
			case 'y': break;
			default: throw asw;
			}
			break;
		}
		catch (char s) {
			cout << s << " : 잘못된 입력" << endl; // 영업시작 다시 질의
		}

	}

	char* file = "날짜 별 판매 기록 파일.txt";
	ofstream fout(file, ios::app); // 항상 파일의 끝에 출력

	int date;
	while (1) {
		try {
			cout << "오늘 날짜 (YYMMDD) : ";
			cin >> date;

			char asw;
			cout << "오늘 날짜 (" << date << ")가 맞습니까? (y/n) ";
			cin >> asw;

			if (asw == 'y') break;
			else throw "다시 입력하세요.";
		}
		catch (char* s) {
			cout << s << endl; // 오늘 날자 다시 입력
		}
	}

	fout << "\n-------<<" << date << ">>-------" << endl;

	while (1) {
		try {
			char asw;
			cout << "새로운 손님(y), 오늘 영업종료(e) : ";
			cin >> asw;
			switch (asw) {
			case 'y':
			{
				countCustomer++;
				Cafe c;
				int total = c.Order(fout);
				sale += total;
				c.printReceipt(total, date);
				continue;
			}
			case 'e': break;
			default: throw asw;
			}
			break;
		}
		catch (char s) {
			cout << s << " : 잘못된 입력" << endl; // 새로운손님, 영업종료 다시 질의
		}
	}

	cout << "오늘 가게의 총 수입 = " << sale << endl;
	fout << "오늘 가게의 총 수입 = " << sale << endl;

	cout << "오늘 손님 수 " << countCustomer << endl;
	fout << "오늘 손님 수 " << countCustomer << endl;

	fout.close();


	while (1) {
		try {
			char asw;
			cout << "날짜 별 판매 기록 파일.txt 열람 후 프로그램 종료(y), 프로그램 종료(e) : ";

			cin >> asw;

			switch (asw) {
			case 'y':
			{
				ifstream fin(file);
				if (!fin) { // 파일이 없으면 못 읽음
					cout << file << " 열기 오류" << endl;
					return 0;
				}

				int c;
				while ((c = fin.get()) != EOF) { // EOF를 만날 때까지 문자 읽기			
					cout << (char)c;
				}


				fin.close();
			}
			case 'e': break;
			default: throw asw;
			}
			break;
		}
		catch (char s) {
			cout << s << " : 잘못된 입력" << endl; // 새로운손님, 영업종료 다시 질의
		}
	}

	system("pause");
}