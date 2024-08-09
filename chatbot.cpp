#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Define a function to process user input
string processInput(string userInput) {
    // Convert input to lowercase for case-insensitive matching
    for (int i = 0; i  <userInput.length(); i++) {
        userInput[i] = tolower(userInput[i]);
    }

    // Define predefined responses
    if (userInput == "hello" || userInput == "hi") {
        return "Hi! How can I help you today?";
    } else if (userInput == "how are you") {
        return "I'm doing great, thanks! How about you?";
    } else if (userInput == "what is your name") {
        return "I'm Chatty, your friendly chatbot!";
    } else if (userInput == "goodbye" || userInput == "bye") {
        return "See you later! Have a great day!";
    } else if (userInput.find("help") != string::npos) {
        return "I can help you with general questions. Try asking me something!";
    } else if (userInput.find("thanks") != string::npos || userInput.find("thank you") != string::npos) {
        return "You're welcome!";
    } else {
        return "I didn't understand that. Can you please rephrase?";
    }
}

int main() {
    cout << "Welcome to Chatty! I'm here to help you with any questions you may have." << endl;

    while (true) {
        cout << "You: ";
        string userInput;
        getline(cin, userInput);

        string response = processInput(userInput);
        cout << "Chatty: " << response << endl;

        if (userInput == "goodbye" || userInput == "bye") {
            break;
        }
    }

    return 0;
}