#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>
#include <cstdlib>
using namespace std;

unordered_map<string, vector<string>> responses = {
    {"greeting", {"Hello! Welcome to our mobile repairing shop. How can I assist you today?", "Hi there! How may I help you with your mobile?", "Welcome! What seems to be the problem with your phone?"}},
    {"farewell", {"Thank you for choosing our mobile repairing services. Have a great day!", "Your satisfaction is our top priority. Goodbye!", "If you have any more questions, feel free to ask. Take care and goodbye!"}},
    {"help", {"Sure, I'm here to help. What issues are you facing with your mobile?", "How can I assist you with your mobile repair? Please let me know.", "I'm here to provide the best possible solutions for your mobile problems. What do you need help with?"}},
    {"screen_cracked", {"A cracked screen is a common issue. We can replace the screen for you. Please bring your mobile to our shop, and our technicians will take care of it.", "Oh no! A cracked screen can be quite bothersome. Don't worry, we offer screen replacement services. Visit our shop, and we'll fix it for you."}},
    {"battery_problem", {"If you're experiencing battery issues, we can replace your mobile's battery. Bring it to our shop, and we'll ensure it gets fixed.", "Battery problems are quite common. We can replace your mobile's battery with a new one. Please visit our shop for assistance."}},
    {"software_issue", {"Software issues can often be resolved by resetting your mobile or updating its software. We can assist you with that. Please bring your phone to our shop, and our technicians will help you out.", "Software problems can be frustrating. We recommend trying a software reset or update. If the issue persists, our technicians can assist you further. Just drop by our shop."}},
    {"water_damage", {"Water damage can be critical for mobiles. We suggest immediately turning off your device and bringing it to our shop for professional repair. Do not attempt to power it on.", "Water damage requires immediate attention. Please switch off your mobile, remove any SIM cards or memory cards, and bring it to our shop. Our experts will assess the damage and offer a suitable solution."}},
    {"default", {"I apologize, but I couldn't understand your request.", "Apologies, I didn't quite get that. Could you please rephrase?", "I'm still learning. Can you provide more information?"}}
};

string respond_to_inquiry(string inquiry) {
    transform(inquiry.begin(), inquiry.end(), inquiry.begin(), ::tolower);
    if (regex_search(inquiry, regex("\\b(?:hello|hi)\\b"))) {
        return responses["greeting"][rand() % responses["greeting"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:goodbye|bye)\\b"))) {
        return responses["farewell"][rand() % responses["farewell"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:help|support)\\b"))) {
        return responses["help"][rand() % responses["help"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:screen|cracked)\\b"))) {
        return responses["screen_cracked"][rand() % responses["screen_cracked"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:battery|charge)\\b"))) {
        return responses["battery_problem"][rand() % responses["battery_problem"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:software|update|reset)\\b"))) {
        return responses["software_issue"][rand() % responses["software_issue"].size()];
    } else if (regex_search(inquiry, regex("\\b(?:water|damage)\\b"))) {
        return responses["water_damage"][rand() % responses["water_damage"].size()];
    } else {
        return responses["default"][rand() % responses["default"].size()];
    }
}

int main() {
    cout << "Welcome to the Customer Interaction Chatbot!" << endl;
    cout << "Type 'exit' to end the conversation." << endl;
    while (true) {
        string user_input;
        cout << "Customer: ";
        getline(cin, user_input);
        if (user_input == "exit") {
            break;
        }
        string bot_response = respond_to_inquiry(user_input);
        cout << "Chatbot: " << bot_response << endl;
    }
    cout << "Thank you for using the Customer Interaction Chatbot. Goodbye!" << endl;
    return 0;
}