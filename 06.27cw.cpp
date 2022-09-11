#include <iostream>
using namespace std;

class Logger {
public:
	Logger *next;
	int priority;
	enum PRIORITY {
		low = 1, med, high
	};

	Logger(int priority) :
			priority(priority) {
		this->next = nullptr;
	}

	Logger* setNext(Logger *next) {
		this->next = next;
		return this->next;
	}

	virtual void print(string)=0;
	void message(string msg, int priority) {
		if (this->priority <= priority) {
			this->print(msg);
			if (this->next)
				this->next->message(msg, priority);
		} else
			cout << "End" << endl;
	}
	virtual ~Logger() {
	}
};

class SMSLogger: public Logger {
public:
	SMSLogger(int priority) :
			Logger(priority) {
	}
	void print(string msg) override {
		cout << "SMS: " << msg << endl;
	}
};

class EmailLogger: public Logger {
public:
	EmailLogger(int priority) :
			Logger(priority) {
	}
	void print(string msg) override {
		cout << "Email: " << msg << endl;
	}
};

class GameLogger: public Logger {
public:
	GameLogger(int priority) :
			Logger(priority) {
	}
	void print(string msg) override {
		cout << "Game: " << msg << endl;
	}
};

class WTFLogger: public Logger {
public:
	WTFLogger(int priority) :
			Logger(priority) {
	}
	void print(string msg) override {
		cout << "WTF is this? " << msg << endl;
	}
};

int main() {
	Logger *start = new SMSLogger(Logger::low);
	start->setNext(new EmailLogger(Logger::med))->setNext(
			new GameLogger(Logger::med))->setNext(new WTFLogger(Logger::high));

	start->message("Hello!", Logger::low);
	start->message("How are you?", Logger::med);
	start->message("Good bye!", Logger::high);

	return 0;
}
