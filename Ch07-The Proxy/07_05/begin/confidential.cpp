#include <iostream>
#include <string>

using namespace std;

class Storage
{
public:
    virtual const string getContents() = 0;
    virtual ~Storage() = default;
};

class SecureStorage : public Storage
{
public:
    explicit SecureStorage(const string &data) : m_Contents(data) {}

    const string getContents()
    {
        return m_Contents;
    }

private:
    const string m_Contents;
};

class SecureStorageProxy : public Storage
{
public:
    explicit SecureStorageProxy(const string &data, const int code): storage(make_unique<SecureStorage>(data)), code(code)
    {

    }

    const string getContents() override
    {
        if (authorized()) {
            return storage->getContents();
        }
        return "Unauthorized";
    }

private:
    bool authorized() {
        return code == 47;
    }

    unique_ptr<SecureStorage> storage;
    int code;
};

int main()
{
    // SecureStorage secureStorage("Top Secret Information");
    SecureStorageProxy secureStorage("Top Secret Information", 47);

    // Limit access to sensitive data
    cout << "Sensitive Data: " << secureStorage.getContents() << endl;

    return 0;
}