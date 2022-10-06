#include <iomanip>
#include <iostream>
#include<vector>
#include<list>
#include<unordered_map>
#include<string>
using namespace std;



enum flag { Noflag, Redflag, Blueflag };
enum fightResult { BothDied, BothAlive, BlueWin, RedWin, NoWar };



int rForce[5]{};
int bForce[5]{};
int rElement[5]{};
int bElement[5]{};



int rwn = 0;
int bwn = 0;

string rName[5]{ "iceman","lion","wolf","ninja","dragon" };
string bName[5]{ "lion","dragon","ninja","iceman","wolf" };


int city_num, head_element, arrow_force, loyalty_decrease, end_time;

class Warrior;
class Warcraft;
class Head;



class Weapon {
public:
	int usage = 0;
	int sforce = 0;
	string name;
	Warrior* owner;
	virtual bool isUsable() {
		return 0;
	};
	virtual void attack(Warrior* p) {
		usage--;
	}
};

class Sword :public Weapon {
public:
	Sword(int k) {
		name = "sword";
		sforce = k / 5;;
	}
	virtual bool isUsable() {
		return sforce > 0;
	};
	virtual void attack(Warrior* p);
};
class Arrow :public Weapon {
public:
	Arrow() {
		name = "arrow";
		usage = 3;
	}
	virtual void attack(Warrior* p);
	virtual bool isUsable() {
		return usage > 0;
	};
};
class Bomb :public Weapon {
public:
	Bomb() {
		usage = 1;
	}
	virtual bool isUsable() {
		return usage > 0;
	};
};

































class Warrior {
public:
	int wnumber;
	int wforce;
	int welement;
	int wlocation;
	string part;
	string name{};
	Sword* sword = nullptr;
	Arrow* arrow = nullptr;
	Bomb* bomb = nullptr;
	Warrior() {}
	double morale = 0;
	int steps = 0;
	int loyalty;
	bool isAlive() {
		return welement > 0;
	}
	bool isLoyal() {
		if (name == "lion" && loyalty <= 0) {
			return false;
		}
		else
		{
			return true;
		}
	}
	friend ostream& operator<<(ostream& o, Warrior& w) {
		o << w.part << " " << w.name << " " << w.wnumber;
		return o;
	}
	friend ostream& operator<<(ostream& o, Warrior* w) {
		o << w->part << " " << w->name << " " << w->wnumber;
		return o;
	}
	void distributeweapon(int i) {
		switch (i)
		{
		case 0:
			sword = new Sword(wforce);
			sword->owner = this;
			break;
		case 2:
			arrow = new Arrow();
			arrow->owner = this;
			break;
		case 1:
			bomb = new Bomb();
			bomb->owner = this;
			break;
		}
	};
	void attack(Warrior* w,int time) {
		if (sword != nullptr) {
			w->welement -= sword->sforce;
			sword->attack(w);
		}
		w->welement -= wforce;
		cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
		cout << *this << " attacked " << w << " in city " << wlocation << " with " << this->welement << " elements and force " << this->wforce<<endl;
	}
	virtual void fightback(Warrior* w,int time) {
		if (sword != nullptr) {
			w->welement -= sword->sforce;
			sword->attack(w);
		}
		w->welement -= wforce / 2;
		cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
		cout << *this << " fought back against " << w << " in city " << wlocation <<endl;
	}
	void boom(Warrior* w,int time,bool first) {
		bool useit = 0;
		if (this->isAlive()&&w->isAlive()) {
			if (bomb != nullptr && w->name != "ninja") {
				if (first) {
					if (sword != nullptr) {
						if (w->welement <= sword->sforce + wforce) {
							;
						}
						else
						{
							if (w->sword != nullptr) {
								if (welement <= w->sword->sforce + w->wforce / 2) {
									useit = 1;
								}
							}
							else
							{
								if (welement <= w->wforce / 2)
									useit = 1;
							}
						}
					}
					else
					{
						if (w->welement <= wforce) {
							;
						}
						else
						{
							if (w->sword != nullptr) {
								if (welement <= w->sword->sforce + w->wforce / 2) {
									useit = 1;
								}
							}
							else
							{
								if (welement <= w->wforce / 2)
									useit = 1;
							}
						}
					}
				}
			}
			if (bomb != nullptr) {
				if (!first) {
					if (w->sword != nullptr) {
						if (welement <= w->sword->sforce + w->wforce) {
							useit = 1;
						}
					}
					else
					{
						if (welement <= w->wforce)
							useit = 1;
					}
				}
			}
			if (useit) {
				w->welement = welement = 0;
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *this << " used a bomb and killed " << w << endl;;
			}
		}
	}
	virtual void march(int d) {
		;
	}
	virtual void yell(fightResult f,int t,bool d) {
		;
	}
	void report(int time) {
		bool sf = 0, af = 0, bf = 0;
		if (sword != nullptr && sword->isUsable()) {
			sf = 1;
		}
		if (arrow != nullptr && arrow->isUsable()) {
			af = 1;
		}
		if (bomb != nullptr && bomb->isUsable()) {
			bf = 1;
		}
		if (!sf&& !af&& !bf) {
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has no weapon" << endl;
		}
		if (sf && !af && bf) {
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *this << " has bomb,sword(" << sword->sforce << ")" << endl;
		}
		if (sf && af && bf) {
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *this << " has arrow(" << arrow->usage << "),bomb,sword(" << sword->sforce << ")" << endl;
		}
		if (sf && af && !bf) {
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has arrow(" <<  arrow->usage << "),sword(" << sword->sforce << ")" << endl;
		}
		if (sf && !af && !bf) {
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has sword(" << sword->sforce << ")" << endl;
		}
		if (!sf && af && !bf)
		{
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has arrow(" <<  arrow->usage<<")" << endl;
		}
		if (!sf && af && bf)
		{
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has arrow(" << arrow->usage << "),bomb"<< endl;
		}
		if (!sf && !af && bf)
		{
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " has bomb" << endl;
		}
	}
	virtual ~Warrior() {
		if (sword != nullptr)
			delete sword;
		if (arrow != nullptr) {
			delete arrow;
		}
		if (bomb != nullptr)
			delete bomb;
	}
	virtual void rub(Warrior* w) {}
};

// About Warrior successors
class Dragon :public Warrior {
public:
	Dragon(string p, int n, int f, int e, int lo, double m) {
		wnumber = n;
		morale = m;
		name = "dragon";
		part = p;
		wforce = f;
		welement = e;
		wlocation = lo;
		distributeweapon(n % 3);
	}
	virtual void yell(fightResult f,int time,bool d) {
		if (f == BothAlive) {
			morale -= 0.2;
		}
		else
		{
			morale += 0.2;
		}
		if (morale >= 0.8&&d) {
			cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
			cout << *this << " yelled in city " << wlocation<<endl;
		}
	}
};

class Ninja :public Warrior {
public:
	virtual void fightback(Warrior* w, int time) override{
		;//do nothing
	}
	Ninja(string p, int n, int f, int e, int lo) {
		wnumber = n;
		name = "ninja";
		part = p;
		wforce = f;
		welement = e;
		wlocation = lo;
		distributeweapon(n % 3);
		distributeweapon((n + 1) % 3);
	}
};

class Iceman :public Warrior {
public:
	Iceman(string p, int n, int f, int e, int lo) {
		wnumber = n;
		name = "iceman";
		part = p;
		wforce = f;
		welement = e;
		wlocation = lo;
		distributeweapon(n % 3);
	}
	virtual void march(int i) {
		steps++;
		if (steps == 2) {
			steps = 0;
			wforce += 20;
			welement -= 9;
			if (welement <= 0) {
				welement = 1;
			}
		}
	}
};

class Lion :public Warrior {
public:
	Lion(string p, int n, int f, int e, int lo, int l) {
		wnumber = n;
		loyalty = l;
		name = "lion";
		part = p;
		wforce = f;
		welement = e;
		wlocation = lo;
	}
};

class Wolf :public Warrior {
public:
	Wolf(string p, int n, int f, int e, int lo) {
		wnumber = n;
		name = "wolf";
		part = p;
		wforce = f;
		welement = e;
		wlocation = lo;
	}
	virtual void rub(Warrior* w) {
		if (w->isAlive() == 0) {
			if (sword != nullptr)
				;
			else
			{
				sword = w->sword;
				w->sword = nullptr;
			}
			if (arrow != nullptr) {
				;
			}
			else
			{
				arrow = w->arrow;
				w->arrow = nullptr;
			}
			if (bomb != nullptr)
				;
			else {
				bomb = w->bomb;
				w->bomb = nullptr;
			}
		}
	}
};








void vanish(Warrior*& p) {
	if (p->sword != nullptr)
		delete p->sword;
	if (p->arrow != nullptr) {
		delete p->arrow;
	}
	if (p->bomb != nullptr)
		delete p->bomb;
	delete p;
	p = nullptr;
}




















class City {
public:
	Warrior* redw = nullptr;
	Warrior* bluew = nullptr;
	int hlocation;
	int helement = 0;
	bool warhappen = 0;
	City() {}
	City(int i) { hlocation = i; }
	fightResult now=NoWar;
	fightResult last=NoWar;
	flag flagstate = Noflag;
	void raiseflag(int time) {
		if (now == last&&warhappen) {
			if (now == RedWin)
			{
				if (flagstate == Redflag) {
					;
				}
				else
				{


					flagstate = Redflag;
					cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
					cout << "red flag raised in city " << hlocation << endl;
				}
			}
			if (now == BlueWin)
			{
				if (flagstate == Blueflag) { ; }
				else {
					flagstate = Blueflag;
					cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
					cout << "blue flag raised in city " << hlocation << endl;
				}
			}
		}
	}
	void award(string pa, Head& h);
	void battle(int time) {
		if (redw != nullptr && bluew != nullptr) {
			warhappen = 1;
		redw->wlocation = hlocation;
		bluew->wlocation = hlocation;
		string rrr = redw->name; string bbb = bluew->name;
		int ee = redw->welement; int ll = bluew->welement;
			if (flagstate == Noflag) {
				if (hlocation % 2 == 0) {
					if (redw->isAlive() && bluew->isAlive()) {
						bluew->attack(redw, time);
						if (redw->isAlive())
							redw->fightback(bluew, time);
						else
						{
							cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
							cout << redw << " was killed in city " << hlocation << endl;
						}
						if (!bluew->isAlive()) {
							cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
							cout << bluew << " was killed in city " << hlocation << endl;
						}
					}
					last = now;
					if (redw->isAlive() && bluew->isAlive()) {
						now = BothAlive;
						if (redw->name == "dragon") {
							redw->yell(now,time,0);
						}
						if (bluew->name == "dragon") {
							bluew->yell(now,time,1);
						}
						if (bluew->name == "lion") {
							bluew->loyalty -= loyalty_decrease;
						}
						if (redw->name == "lion") {
							redw->loyalty -= loyalty_decrease;
						}
					}
					else if(redw->isAlive() && !bluew->isAlive())
					{
						redw->rub(bluew);
						delete bluew;
						bluew = nullptr;
						now = RedWin;
						if (redw->name == "dragon") {
							redw->yell(now,time,0);
						}
					}
					else if (!redw->isAlive() && bluew->isAlive()) {
						bluew->rub(redw);
						delete redw;
						redw = nullptr;
						now = BlueWin;
						if (bluew->name == "dragon") {
							bluew->yell(now,time,1);
						}
					}
					else {
						warhappen = 0;
						delete redw;
						redw = nullptr;
						delete bluew;
						bluew = nullptr;
					}
				}
				else
				{
					if (redw->isAlive() && bluew->isAlive()) {
						redw->attack(bluew, time);
						if (bluew->isAlive())
							bluew->fightback(redw, time);
						else
						{
							cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
							cout << bluew << " was killed in city " << hlocation << endl;
						}
						if (!redw->isAlive()) {
							cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
							cout << redw << " was killed in city " << hlocation << endl;
						}
					}
					last = now;
					if (redw->isAlive() && bluew->isAlive()) {
						now = BothAlive;
						if (redw->name == "dragon") {
							redw->yell(now, time,1);
						}
						if (bluew->name == "dragon") {
							bluew->yell(now, time,0);
						}if (bluew->name == "lion") {
							bluew->loyalty -= loyalty_decrease;
						}
						if (redw->name == "lion") {
							redw->loyalty -= loyalty_decrease;
						}
					}
					else if (redw->isAlive() && !bluew->isAlive())
					{
						redw->rub(bluew);
						delete bluew;
						bluew = nullptr;
						now = RedWin;
						if (redw->name == "dragon") {
							redw->yell(now, time,1);
						}
					}
					else if (!redw->isAlive() && bluew->isAlive()) {
						bluew->rub(redw);
						delete redw;
						redw = nullptr;
						now = BlueWin;
						if (bluew->name == "dragon") {
							bluew->yell(now, time,0);
						}
					}
					else {
						warhappen = 0;
						delete redw;
						redw = nullptr;
						delete bluew;
						bluew = nullptr;
					}
				}
			}
			else if (flagstate == Blueflag)
			{
				if (redw->isAlive() && bluew->isAlive()) {
					bluew->attack(redw, time);
					if (redw->isAlive())
						redw->fightback(bluew, time);
					else
					{
						cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
						cout << redw << " was killed in city " << hlocation << endl;
					}
					if (!bluew->isAlive()) {
						cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
						cout << bluew << " was killed in city " << hlocation << endl;
					}
				}
				last = now;
				if (redw->isAlive() && bluew->isAlive()) {
					now = BothAlive;
					if (redw->name == "dragon") {
						redw->yell(now, time,0);
					}
					if (bluew->name == "dragon") {
						bluew->yell(now, time,1);
					}if (bluew->name == "lion") {
						bluew->loyalty -= loyalty_decrease;
					}
					if (redw->name == "lion") {
						redw->loyalty -= loyalty_decrease;
					}
				}
				else if (redw->isAlive() && !bluew->isAlive())
				{
					redw->rub(bluew);
					delete (bluew); bluew = nullptr;
					now = RedWin;
					if (redw->name == "dragon") {
						redw->yell(now, time,0);
					}
				}
				else if (!redw->isAlive() && bluew->isAlive()) {
					bluew->rub(redw);
					delete (redw); redw = nullptr;
					now = BlueWin;
					if (bluew->name == "dragon") {
						bluew->yell(now, time,1);
					}
				}
				else {
					warhappen = 0;
					delete redw;
					redw = nullptr;
					delete bluew;
					bluew = nullptr;
				}
			}
			else if (flagstate == Redflag) {
			if (redw->isAlive() && bluew->isAlive()) {
				redw->attack(bluew, time);
				if (bluew->isAlive())
					bluew->fightback(redw, time);
				else
				{
					cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
					cout << bluew << " was killed in city " << hlocation << endl;
				}
				if (!redw->isAlive()) {
					cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
					cout << redw << " was killed in city " << hlocation << endl;
				}
			}
				last = now;
				if (redw->isAlive() && bluew->isAlive()) {
					now = BothAlive;
					if (redw->name == "dragon") {
						redw->yell(now, time,1);
					}
					if (bluew->name == "dragon") {
						bluew->yell(now, time,0);
					}
					if (bluew->name == "lion") {
						bluew->loyalty-=loyalty_decrease;
					}
					if (redw->name == "lion") {
						redw->loyalty -= loyalty_decrease;
					}
				}
				else if (redw->isAlive() && !bluew->isAlive())
				{
					redw->rub(bluew);
					delete (bluew); bluew = nullptr;
					now = RedWin;
					if (redw->name == "dragon") {
						redw->yell(now, time,1);
					}
				}
				else if (!redw->isAlive() && bluew->isAlive()) {
					bluew->rub(redw);
					delete (redw); redw = nullptr;
					now = BlueWin;
					if (bluew->name == "dragon") {
						bluew->yell(now, time,0);
					}
				}
				else {
					warhappen = 0;
					delete redw;
					redw = nullptr;
					delete bluew;
					bluew = nullptr;
				}
			}
			if (warhappen&&now == RedWin&&bbb=="lion") {
				if(ll>0)
				redw->welement += ll;
			}
			else if (warhappen&&now == BlueWin&&rrr=="lion")
			{
				if(ee>0)
				bluew->welement += ee;
			}
			if (warhappen&&now == RedWin) {
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << redw << " earned " << helement << " elements for his headquarter" << endl;
			}
			else if (warhappen&&now == BlueWin)
			{
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << bluew << " earned " << helement << " elements for his headquarter" << endl;
			}
			raiseflag(time);
		}
		else
		{
		if (redw != nullptr && !redw->isAlive())
		{
			delete redw;
			redw = nullptr;
		}
		if (bluew != nullptr && !bluew->isAlive())
		{
			delete bluew;
			bluew = nullptr;
		}
		warhappen = 0;
		;
		}
	}
};
















class Head :public City {
public:
	int enemycount = 0;
	int hnumber = 0;;
	string part;
	bool born = 0;
	vector<Warrior*> troop;
	Head() {}
	bool isTaken() {
		return enemycount == 2;
	}
	Head(const string p) {
		part = p;
		if (part == "red")
			hlocation = 0;
		else if (part == "blue")
		{
			hlocation = city_num + 1;
		}
		helement = head_element;
	}
	void makeWarrior(int time) {
		if (part == "red") {
			if (helement >= rElement[hnumber % 5]) {
				born = 1;
				Warrior* np;
				helement -= rElement[hnumber % 5];
				switch (hnumber % 5)
				{
				case 0:
					np = new Iceman("red", hnumber + 1, rForce[hnumber % 5], rElement[hnumber % 5], 0);
					break;
				case 1:
					np = new Lion("red", hnumber + 1, rForce[hnumber % 5], rElement[hnumber % 5], 0, helement);
					break;
				case 2:
					np = new Wolf("red", hnumber + 1, rForce[hnumber % 5], rElement[hnumber % 5], 0);
					break;
				case 3:
					np = new Ninja("red", hnumber + 1, rForce[hnumber % 5], rElement[hnumber % 5], 0);
					break;
				case 4:
					np = new Dragon("red", hnumber + 1, rForce[hnumber % 5], rElement[hnumber % 5], 0, (double)helement / rElement[4]);
					break;
				}
				troop.push_back(np);
				hnumber++;
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *np << " born" << endl;
				if (np->name == "lion")
				{
					cout << "Its loyalty is " << np->loyalty << endl;
				}
				if (np->name == "dragon")
				{
					cout << "Its morale is " <<fixed<<setprecision(2)<< np->morale << endl;
				}
			}
		}
		else if (part == "blue")
		{
			if (helement >= bElement[hnumber % 5]) {
			born = 1;
				Warrior* np;
				helement -= bElement[hnumber % 5];
				switch (hnumber % 5)
				{
				case 3:
					np = new Iceman("blue", hnumber + 1, bForce[hnumber % 5], bElement[hnumber % 5], city_num + 1);

					break;
				case 0:
					np = new Lion("blue", hnumber + 1, bForce[hnumber % 5], bElement[hnumber % 5], city_num + 1, helement);

					break;
				case 4:
					np = new Wolf("blue", hnumber + 1, bForce[hnumber % 5], bElement[hnumber % 5], city_num + 1);

					break;
				case 2:
					np = new Ninja("blue", hnumber + 1, bForce[hnumber % 5], bElement[hnumber % 5], city_num + 1);
					break;
				case 1:
					np = new Dragon("blue", hnumber + 1, bForce[hnumber % 5], bElement[hnumber % 5], city_num + 1, (double)helement / bElement[1]);
					break;
				}
				troop.push_back(np);
				hnumber++;
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *np << " born" << endl;
				if (np->name == "lion")
				{
					cout << "Its loyalty is " << np->loyalty << endl;
				}
				if (np->name == "dragon")
				{
					cout << "Its morale is " <<fixed << setprecision(2)<< np->morale << endl;
				}
			}
		}
	}
	void lionrun(int time) {
		for (int i = 0; i != troop.size(); i++) {
			if (troop[i]->name == "lion" && !troop[i]->isLoyal())
			{
				cout << setw(3) << setfill('0') << time / 60 << ":" << setw(2) << setfill('0') << time % 60 << ' ';;
				cout << *troop[i] << " ran away" << endl;
			}
		}
	}
};































class Warcraft {
public:
	Head red{ "red" };
	Head blue{ "blue" };
	vector<City*> city;
	int nowtime = 0;
	Warcraft() {
		city.push_back(&red);
		for (int i = 1; i <= city_num; i++) {
			City* c = new City(i);
			city.push_back(c);
		}
		city.push_back(&blue);
	}
	void Timeprocess() {
		while (nowtime <= end_time&&!red.isTaken()&&!blue.isTaken())
		{
			switch (nowtime % 60)
			{
			case 0:
				do00();
				break;
			case 5:
				do05();
				break;
			case 10:
				do10();

				break;
			case 20:
				do20();
				break;
			case 30:
				do30();
				break;
			case 35:
				do35();
				break;
			case 38:
				do38();
				break;
			case 40:
				do40();
				break;
			case 50:
				do50();
				break;
			case 55:
				do55();
				break;
			}
			++nowtime;
		}
	}
	void do00() {
		red.born = 0;
		blue.born = 0;
		red.makeWarrior(nowtime);
		blue.makeWarrior(nowtime);
	}
	void do05() {
		if (red.born && red.troop[red.hnumber - 1] != nullptr && red.troop[red.hnumber - 1]->name == "lion") {
			if (red.troop[red.hnumber - 1]->isLoyal() == 0) {
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << red.troop[red.hnumber - 1] << " ran away" << endl;
				delete red.troop[red.hnumber - 1];
				red.troop[red.hnumber - 1] = nullptr;
			}
		}
		for (int i = 1; i < city_num + 1; i++) {
			if (city[i]->redw != nullptr && city[i]->redw->name == "lion" && !city[i]->redw->isLoyal()) {
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i]->redw << " ran away" << endl;
				delete city[i]->redw;
				city[i]->redw = nullptr;
			}
			if (city[i]->bluew != nullptr && city[i]->bluew->name == "lion" && !city[i]->bluew->isLoyal()) {
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i]->bluew << " ran away" << endl;
				delete city[i]->bluew;
				city[i]->bluew = nullptr;
			}
		}
		if (blue.born&&blue.troop[blue.hnumber - 1] != nullptr && blue.troop[blue.hnumber - 1]->name == "lion") {
			if (blue.troop[blue.hnumber - 1]->isLoyal() == 0) {
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << blue.troop[blue.hnumber - 1] << " ran away" << endl;
				delete blue.troop[blue.hnumber - 1];
				blue.troop[blue.hnumber - 1] = nullptr;
			}
		}
	}
	void do10() {
		if (city[1]->bluew != nullptr) {
			city[1]->bluew->march(1);
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << city[1]->bluew << " reached red headquarter " << "with " << city[1]->bluew->welement << " elements and force " << city[1]->bluew->wforce << endl;
			red.enemycount++;
			if (city[0]->bluew != nullptr) {
				city[0]->redw = city[1]->bluew;
			}
			else
			{
				city[0]->bluew = city[1]->bluew;
			}
			city[1]->bluew = nullptr;
		}
		if (red.isTaken())
		{
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << "red headquarter was taken" << endl;
		}
		if (red.born&& red.troop[red.hnumber - 1]!=nullptr) {
			red.troop[red.hnumber - 1]->march(1);
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << red.troop[red.hnumber - 1] << " marched to city " << 1 << " with " << red.troop[red.hnumber - 1]->welement << " elements and force " << red.troop[red.hnumber - 1]->wforce << endl;
		}
		for (int i = 1; i < city_num + 1; i++) {
			if (i > 1 && city[i - 1]->redw != nullptr) {
				city[i - 1]->redw->march(1);
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i - 1]->redw << " marched to city " << i << " with " << city[i - 1]->redw->welement << " elements and force " << city[i - 1]->redw->wforce << endl;
			}
			if (i < city_num&& city[i + 1]->bluew != nullptr) {
				city[i + 1]->bluew->march(-1);
				city[i]->bluew = city[i + 1]->bluew;
				city[i + 1]->bluew = nullptr;
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i]->bluew << " marched to city " << i << " with " << city[i]->bluew->welement << " elements and force " << city[i]->bluew->wforce << endl;
			}
		}
		if (blue.born&&blue.troop[blue.hnumber - 1] != nullptr) {
			blue.troop[blue.hnumber - 1]->march(1);
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << blue.troop[blue.hnumber - 1] << " marched to city " << city_num << " with " << blue.troop[blue.hnumber - 1]->welement << " elements and force " << blue.troop[blue.hnumber - 1]->wforce << endl;
		}
		if (city[city_num]->redw != nullptr) {
			city[city_num]->redw->march(1);
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << city[city_num]->redw << " reached blue headquarter " << "with " << city[city_num]->redw->welement << " elements and force " << city[city_num]->redw->wforce << endl;
			blue.enemycount++;
			if (city[city_num+1]->redw != nullptr) {
				city[city_num+1]->bluew = city[city_num]->redw;
			}
			else
			{
				city[city_num+1]->redw = city[city_num]->redw;
			}
			city[city_num]->redw = nullptr;
		}

		if (blue.isTaken())
		{
			cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
			cout << "blue headquarter was taken" << endl;
		}
		if(blue.born&& blue.troop[blue.hnumber - 1] != nullptr)
		city[city_num]->bluew = blue.troop[blue.hnumber - 1];
		for (int i = city_num + 1; i > 1; i--) {
			if (city[i - 1]->redw != nullptr) {
				city[i]->redw = city[i - 1]->redw;
				city[i - 1]->redw = nullptr;
			}
		}
		if (red.born&& red.troop[red.hnumber - 1]!=nullptr)
		{		city[1]->redw = red.troop[red.hnumber - 1];
	}
	}
	void do20() {
		for (int i = 1; i <= city_num; i++) {
			city[i]->helement += 10;
		}
	}
	void do30() {
		for (int i = 1; i <= city_num; i++) {
			if (city[i]->redw != nullptr && city[i]->bluew == nullptr) {
				red.helement += city[i]->helement;
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i]->redw << " earned "<<city[i]->helement<<" elements for his headquarter" << endl;
				city[i]->helement = 0;
			}
			if (city[i]->redw == nullptr && city[i]->bluew != nullptr) {
				blue.helement += city[i]->helement;
				cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
				cout << city[i]->bluew << " earned " << city[i]->helement << " elements for his headquarter" << endl;
				city[i]->helement = 0;
			}
		}
	}
	void do35() {
		for (int i = 0; i <= city_num + 1; i++) {
			if (i < city_num) {
				if (city[i]->redw != nullptr && city[i + 1]->bluew != nullptr && city[i]->redw->arrow != nullptr && city[i]->redw->arrow->isUsable()) {
					city[i]->redw->arrow->attack(city[i + 1]->bluew);
					if (city[i + 1]->bluew->isAlive()) {
						cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
						cout << city[i]->redw << " shot" << endl;
					}
					else
					{
						cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
						cout << city[i]->redw << " shot" << " and killed " << city[i + 1]->bluew << endl;;
					}
				}
			}
			if (i > 0) {
				if (city[i]->bluew != nullptr && city[i - 1]->redw != nullptr && city[i]->bluew->arrow != nullptr && city[i]->bluew->arrow->isUsable()) {
					city[i]->bluew->arrow->attack(city[i - 1]->redw);
					if (city[i - 1]->redw->isAlive()) {
						cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
						cout << city[i]->bluew << " shot" << endl;
					}
					else
					{
						cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
						cout << city[i]->bluew << " shot" << " and killed " << city[i - 1]->redw << endl;;
					}
				}
			}
		}
	}
	void do38() {
		for (int i = 1; i < city_num + 1; i++) {
			if (city[i]->redw != nullptr && city[i]->bluew != nullptr)
			{		
				if (city[i]->flagstate == Noflag) {
					if (i % 2 == 0)
					{
						city[i]->redw->boom(city[i]->bluew, nowtime,0);
						city[i]->bluew->boom(city[i]->redw, nowtime,1);
					}
					else
					{
						city[i]->redw->boom(city[i]->bluew, nowtime,1);
						city[i]->bluew->boom(city[i]->redw, nowtime,0);
					}
				}
				else if (city[i]->flagstate == Redflag) {
					city[i]->redw->boom(city[i]->bluew, nowtime,1);
					city[i]->bluew->boom(city[i]->redw, nowtime,0);
				}
				else if (city[i]->flagstate == Blueflag) {
					city[i]->redw->boom(city[i]->bluew, nowtime,0);
					city[i]->bluew->boom(city[i]->redw, nowtime,1);
				}
		}
		}
	}
	void do40() {
		for (int i = 1; i < city_num + 1; i++) {
			city[i]->battle(nowtime);
		}
		for (int i = city_num; i >0; i--) {
			city[i]->award("red",red);
		}
		for (int i = 1; i < city_num + 1; i++) {
			city[i]->award("blue",blue);
		}
		for (int i = 1; i < city_num + 1; i++) {
			if (city[i]->now == RedWin&&city[i]->warhappen) {
				red.helement += city[i]->helement;
				city[i]->helement = 0;
			}
			if (city[i]->now == BlueWin&&city[i]->warhappen) {
				blue.helement += city[i]->helement;
				city[i]->helement = 0;
			}
		}
	}
	void do50() {
		cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
		cout << red.helement <<" elements in red headquarter"<< endl;
		cout << setw(3) << setfill('0') << nowtime / 60 << ":" << setw(2) << setfill('0') << nowtime % 60 << ' ';;
		cout << blue.helement << " elements in blue headquarter" << endl;
	}
	void do55() {
		for (int i = 0; i < city_num + 2; i++) {
			if(i!=0&&city[i]->redw!=nullptr)
			city[i]->redw->report(nowtime);
		}
		if(city[city_num + 1]->bluew!=nullptr)
		city[city_num + 1]->bluew->report(nowtime);
		if(city[0]->redw!=nullptr)
		city[0]->redw->report(nowtime);
		for (int i = 0; i < city_num + 2; i++) {
			if (city[i]->bluew != nullptr)
			city[i]->bluew->report(nowtime);
		}
	}
};

























void Sword::attack(Warrior* p) {
	usage++;
	sforce *= 4;
	sforce /= 5;
}
void Arrow::attack(Warrior* p) {
	usage--;
	p->welement -= arrow_force;
}


void City::award(string pa, Head& h) {
	if (pa == "red")
	{
		if (now == RedWin&&warhappen==1) {
			if (h.helement >= 8) {
				h.helement -= 8;
				redw->welement += 8;
			}
		}
	}
	else
	{
		if (now == BlueWin && warhappen == 1) {
			if (h.helement >= 8) {
				h.helement -= 8;
				bluew->welement += 8;
			}
		}
	}
}
























































int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ":" << endl;
		cin >> head_element >> city_num >> arrow_force >> loyalty_decrease >> end_time;
		cin >> rElement[4] >> rElement[3] >> rElement[0] >> rElement[1] >> rElement[2];
		cin >> rForce[4] >> rForce[3] >> rForce[0] >> rForce[1] >> rForce[2];
		bForce[0] = rForce[1];
		bElement[0] = rElement[1];
		bForce[1] = rForce[4];
		bElement[1] = rElement[4];
		bForce[2] = rForce[3];
		bElement[2] = rElement[3];
		bForce[3] = rForce[0];
		bElement[3] = rElement[0];
		bForce[4] = rForce[2];
		bElement[4] = rElement[2];
		Warcraft warcraft;
		warcraft.Timeprocess();
	}
	return 0;
}
