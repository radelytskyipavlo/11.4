#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <sstream>
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YourProjectTests
{
    TEST_CLASS(FriendManagementTests)
    {
    public:

        TEST_METHOD(CreateFriendListTest)
        {
            const string filename = "testfile.bin"; 
            const int numFriends = 2;
            stringstream input("wqe eas\n1234567890\n1 1 1990\nGatg SGeew\n0987654321\n2 2 2000\n");
            streambuf* oldcin = cin.rdbuf(input.rdbuf());

            createFriendList(filename);
            cin.rdbuf(oldcin);
            ifstream file(filename, ios::binary); 
            Assert::IsTrue(file.is_open());

            Friend friends[numFriends];
            for (int i = 0; i < numFriends; ++i) {
                file.read(reinterpret_cast<char*>(&friends[i]), sizeof(Friend)); 
            }

            file.close();

            Assert::AreEqual(string("wqe"), string(friends[0].firstName));
            Assert::AreEqual(string("eas"), string(friends[0].lastName));
            Assert::AreEqual(string("1234567890"), string(friends[0].phoneNumber));
            Assert::AreEqual(1, friends[0].birthday[0]);
            Assert::AreEqual(1, friends[0].birthday[1]);
            Assert::AreEqual(1990, friends[0].birthday[2]);

            remove(filename.c_str()); 
        }
    };
}
