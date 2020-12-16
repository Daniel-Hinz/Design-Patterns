// traversing genealogical tree using Composite and Visitors
// Daniel Hinz
// 11/27/2020

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl; using std::cin;
using std::string; using std::vector;

class Person { 
public:
	Person(string firstName, Person *spouse, Person *father, Person *mother) :
		firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
	
	const string & getFirstName() { return firstName_; }
	Person *getFather() { return father_; }
	Person *getSpouse() { return spouse_; }
	Person *getMother() { return mother_; }

	void setSpouse(Person *spouse) { spouse_ = spouse; }
	virtual string getName() = 0;
	virtual void accept(class PersonVisitor *) = 0;
	virtual ~Person() {}

private:
	const string firstName_;
	Person *spouse_;
	Person *father_;
	Person *mother_;
};


// leaf 
class Man : public Person {
public:
	Man(string lastName, string firstName, Person *spouse, Person *father, Person *mother) : 
		lastName_(lastName), Person(firstName, spouse, father, mother) {}

	void accept(class PersonVisitor *visitor) override;
	string getName() { return getFirstName() + " " + lastName_; }
	const string &getLastName() { return lastName_; }

private:
	const string lastName_;
};

// composite
class Woman : public Person {
public:
	Woman(vector<Person*> children, string firstName, Person *spouse, Person *father, Person *mother) : 
		children_(children), Person(firstName, spouse, father, mother) {}

	const vector<Person*> &getChildren() { return children_; }
	void setChildren(const vector<Person*> &children) { children_ = children; }
	void accept(class PersonVisitor *visitor) override;
	string getName() {
		if (getSpouse() != nullptr) return getFirstName() + " " + static_cast<Man*>(getSpouse())->getLastName();
		else if (getFather() != nullptr) return getFirstName() + " " + static_cast<Man*>(getFather())->getLastName();
		else return getFirstName();
	}

private:
	vector<Person *> children_;
};

// abstract visitor
class PersonVisitor {
public:
	virtual void visit(Man*) = 0;
	virtual void visit(Woman*) = 0;
	virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
	visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor) {
	visitor->visit(this);

	for (auto child : children_) {
		child->accept(visitor);

		// check for spouses
		if (child->getSpouse() != nullptr)
			child->getSpouse()->accept(visitor);
	}
}

// concrete visitors the last name for a man is stored in object
class NamePrinter : public PersonVisitor {
public:
	void visit(Man *m) override {
		cout << m->getFirstName() << " " << m->getLastName() << endl;
	}
	void visit(Woman *w) override {
		cout << w->getFirstName() << " ";
		if (w->getSpouse() != nullptr)
			cout << static_cast<Man *> (w->getSpouse())->getLastName();
		else if (w->getFather() != nullptr)
			cout << static_cast<Man *> (w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};

// prints children
class ChildrenPrinter : public PersonVisitor {
public:
	void visit(Man *m) override {
		cout << m->getFirstName() << ": ";
		Woman *spouse = static_cast<Woman *>(m->getSpouse());
		if (spouse != nullptr)
			printNames(spouse->getChildren());
		cout << endl;
	}
	void visit(Woman *w) override {
		cout << w->getFirstName() << ": ";
		printNames(w->getChildren());
		cout << endl;
	}
private:
	void printNames(const vector<Person *> &children) {
		for (const auto c : children)
			cout << c->getFirstName() << ", ";
	}
};

// prints maiden names of all women
class printMaiden : public PersonVisitor {
public:
	void visit(Woman *woman) override {
		if (woman->getFather() != nullptr) 
			cout << woman->getFirstName() << "'s maiden name is: " << static_cast<Man*>(woman->getFather())->getLastName() << endl;
		else 
			cout << woman->getFirstName() << "'s maiden name is: Doe" << endl;
	}	

	void visit(Man *man) override { 
//		cout << man->getFirstName() << " " << man->getLastName() << endl;
	}
};

// see if two individuals can get married
class marriage : public PersonVisitor {
public:
	     marriage  (string first, string second) : first_(first), second_(second) {}
	bool getMarried() { return married_; }

	void visit(Woman *woman) override {
		// if names are the same return false (herself)
		if (first_ == second_)
			married_ = false;

		// if already married return false (already married)
		if (woman->getSpouse() != nullptr && (woman->getName() == first_ || woman->getName() == second_))
			married_ = false;
	
		// if siblings return false (siblings)
		if (woman->getMother() != nullptr && (woman->getName() == first_ || woman->getName() == second_)) {
			for (auto child : static_cast<Woman*>(woman->getMother())->getChildren()) {
				if (child->getName() == first_ || child->getName() == second_)
					married_ = false;
			}
		}

		// if parents return false (parents/children)
		if (woman->getName() == first_ || woman->getName() == second_) {
			for (auto child : static_cast<Woman*>(woman)->getChildren()) {
				if (child->getName() == second_)
					married_ = false;
			}
		}

		// if aunt/uncle return false (aunt/uncle)
		if ((woman->getName() == first_ || woman->getName() == second_) && woman->getMother() != nullptr && woman->getMother()->getMother() != nullptr) {
			for (auto child : static_cast<Woman*>(woman->getMother()->getMother())->getChildren()) {
				if (child->getName() == second_) 
					married_ = false;
			}
		}
		else if ((woman->getName() == first_ || woman->getName() == second_) && woman->getFather() != nullptr && woman->getFather()->getMother() != nullptr) {
			for (auto child : static_cast<Woman*>(woman->getFather()->getMother())->getChildren()) {
				if (child->getName() == second_)
					married_ = false;
			}
		}
	}

	void visit(Man *man) override {
		// if names are the same return false (hisself)
		if (first_ == second_) 
			married_ = false;

		// if already married return false (already married) 
		if (man->getSpouse() != nullptr && (man->getName() == first_ || man->getName() == second_))
			married_ = false;

		// if siblings return false (siblings)
		if (man->getMother() != nullptr && (man->getName() == first_ || man->getName() == second_)) {
			for (auto child : static_cast<Woman*>(man->getMother())->getChildren()) {
				if (child->getName() == first_ || child->getName() == second_)
					married_ = false;
			}
		}

		// if aunt/uncle return false (aunt/uncle)
		if ((man->getName() == first_ || man->getName() == second_) && man->getMother() != nullptr && man->getMother()->getMother() != nullptr) {
			for (auto child : static_cast<Woman*>(man->getMother()->getMother())->getChildren()) {
				if (child->getName() == second_)
					married_ = false;
			}
		}
		else if ((man->getName() == first_ || man->getName() == second_) && man->getFather() != nullptr && man->getFather()->getMother() != nullptr) {
			for (auto child : static_cast<Woman*>(man->getFather()->getMother())->getChildren()) {
				if (child->getName() == second_)
					married_ = false;
			}
		}
	}

private:
	string  first_;
	string second_;
	bool  married_ = true;
};

// demonstrating the operation
int main() {

	// setting up the genealogical tree:      
	//
	//       James Smith  <--spouse-->   Mary 
	//	                                  |
	//	                                 children -------------------------
	//	                                  |              |                |
	//	                                  |              |                |
	//	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
	//	                                  |
	//	                                 children------------
	//	                                  |                 |
	//                                    |                 |
	//	   Jennifer  <--spouse-->  Michael Johnson      Barbara
	//	       |
	//	    children
	//	       |
	//         |
	//	     Susan

	// first generation
	Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
	Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
	ms->setSpouse(js); js->setSpouse(ms);

	// second generation
	Woman *ps = new Woman({}, "Patricia", nullptr, js, ms);
	Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
	ps->setSpouse(wj); wj->setSpouse(ps);

	// set marys kids
	vector<Person *> marysKids = { ps, new Man("Smith", "Robert", nullptr, js, ms), new Woman({}, "Linda", nullptr, js, ms) };
	ms->setChildren(marysKids);

	// third generation
	Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
	vector<Person *> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
	ps->setChildren(patsKids);

	// set jens kids
	Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
	vector<Person *> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

	jj->setSpouse(mj); mj->setSpouse(jj);
	jj->setChildren(jensKids);

	// defining two visitors
	ChildrenPrinter *cp = new ChildrenPrinter;
	NamePrinter *np = new NamePrinter;

	// print maiden names
	printMaiden *pm = new printMaiden;

	cout << "Printing women's maiden names..." << endl;
	ms->accept(pm);

	// ask for names
	cout << "\nChecking 5 pairs for marriage compatibility..." << endl;

	for (auto i = 0; i < 5; ++i) {
		std::string first, second;
		cout << "Enter a first candidate: ";
		std::getline(cin, first);

		cout << "Enter a second candidate: ";
		std::getline(cin, second);

		// see if they can marry
		marriage* cm = new marriage(first, second);
		ms->accept(cm);

		// print if they can marr
		if (cm->getMarried()) cout << "\nThey can marry\n";
		else cout << "\nThey can not marry\n";
	}
	cout << "Finished" << endl;
	return 0;
}
