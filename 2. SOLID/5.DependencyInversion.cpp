#include <iostream>
#include <string>

/*ISP--High-level modules should not depend on low-level modules. Both should depend on abstractions.*/

class DBConnectionInterface {
public:
    virtual std::string connect() = 0;
    virtual ~DBConnectionInterface() {};
};

class MySQLConnection : public DBConnectionInterface {
public:
    std::string connect() override {
        // handle the database connection
        return "Database connection";
    }
};

class PostgreSQLConnection : public DBConnectionInterface {
public:
    std::string connect() override {
        // handle PostgreSQL database connection
        return "PostgreSQL connection";
    }
};

class PasswordReminder {
private:
    DBConnectionInterface* dbConnection;

public:
    PasswordReminder(DBConnectionInterface* dbConnection) : dbConnection(dbConnection) {}

    // Added this method to demonstrate usage of the injected connection
    std::string sendReminder() {
        return dbConnection->connect();
    }
};

int main() {
    MySQLConnection mysql;
    PasswordReminder pr1(&mysql);
    std::cout << pr1.sendReminder() << std::endl;

    PostgreSQLConnection pg;
    PasswordReminder pr2(&pg);
    std::cout << pr2.sendReminder() << std::endl;

    return 0;
}