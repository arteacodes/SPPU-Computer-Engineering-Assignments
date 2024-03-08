#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to ask yes/no questions
bool askQuestion(const string& question) {
    char response;
    cout << question << " (y/n): ";
    cin >> response;
    return (response == 'y' || response == 'Y');
}

// Function to diagnose allergies
bool diagnoseAllergies() {
    bool itchingOrSwelling = askQuestion("Do you experience any itching or swelling?");
    bool redness = askQuestion("Do you have red, watery eyes?");
    return (itchingOrSwelling || redness);
}

// Function to diagnose fever
bool diagnoseFever() {
    bool highTemperature = askQuestion("Do you have a temperature above 37.5°C?");
    bool chills = askQuestion("Do you experience chills?");
    return (highTemperature || chills);
}

// Function to diagnose cold
bool diagnoseCold() {
    bool runnyOrStuffyNose = askQuestion("Do you have a runny or stuffy nose?");
    bool sneezing = askQuestion("Are you sneezing frequently?");
    return (runnyOrStuffyNose || sneezing);
}

// Function to diagnose flu
bool diagnoseFlu() {
    bool bodyAches = askQuestion("Do you have body aches?");
    bool fatigue = askQuestion("Do you feel tired or fatigued?");
    bool highTemperature = askQuestion("Do you have a temperature above 38°C?");
    return (bodyAches && fatigue && highTemperature);
}

// Function to diagnose strep throat
bool diagnoseStrepThroat() {
    bool soreThroat = askQuestion("Do you have a sore throat?");
    bool swollenTonsils = askQuestion("Are your tonsils swollen?");
    return (soreThroat && swollenTonsils);
}

// Function to diagnose food poisoning
bool diagnoseFoodPoisoning() {
    bool nausea = askQuestion("Do you feel nauseous?");
    bool vomiting = askQuestion("Have you been vomiting?");
    bool diarrhea = askQuestion("Do you have diarrhea?");
    return (nausea && vomiting && diarrhea);
}

// Function to diagnose appendicitis
bool diagnoseAppendicitis() {
    bool severeAbdominalPain = askQuestion("Do you have severe abdominal pain?");
    bool lossOfAppetite = askQuestion("Have you lost your appetite?");
    return (severeAbdominalPain && lossOfAppetite);
}

int main() {
    cout << "Welcome to the Expert System for Medical Diagnosis\n";

    bool hasAllergies = diagnoseAllergies();

    bool hasFever = diagnoseFever();

    bool hasCold = diagnoseCold();

    bool hasFlu = diagnoseFlu();

    bool hasStrepThroat = diagnoseStrepThroat();

    bool hasFoodPoisoning = diagnoseFoodPoisoning();

    bool hasAppendicitis = diagnoseAppendicitis();


    // Output diagnosis
    cout << "\nDiagnosis:\n";

    if (hasAllergies) {
        cout << "You may have allergies.\n";
    }
    if (hasFever) {
        cout << "You may have a fever.\n";
    }
    if (hasCold) {
        cout << "You may have a cold.\n";
    }
    if (hasFlu) {
        cout << "You may have flu.\n";
    }
    if (hasStrepThroat) {
        cout << "You may have a throat infection.\n";
    }
    if (hasFoodPoisoning) {
        cout << "You may have food poisoning.\n";
    }
    if (hasAppendicitis) {
        cout << "You may have appendicitis.\n";
    }

    // If none of the conditions are met
    if (!hasAllergies && !hasFever && !hasCold && !hasFlu && !hasStrepThroat && !hasFoodPoisoning && !hasAppendicitis) {
        cout << "No specific diagnosis could be made based on the provided symptoms.\n";
    }

    cout<<endl;

    return 0;
}
