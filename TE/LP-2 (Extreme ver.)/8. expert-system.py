"""
This code implements a simple expert system similar to MYCIN that providea expert opinions based on user input regarding symptoms.
"""


# function to ask yes/no questions
def ask_question(question):
    response = input(question + " (y/n): ").strip().lower()
    return response == 'y'


def diagnose_allergies():
    itching_or_swelling = ask_question("Do you experience any itching or swelling?")
    redness = ask_question("Do you have red, watery eyes?")
    return itching_or_swelling or redness


def diagnose_fever():
    high_temperature = ask_question("Do you have a temperature above 37.5°C?")
    chills = ask_question("Do you experience chills?")
    return high_temperature or chills


def diagnose_cold():
    runny_or_stuffy_nose = ask_question("Do you have a runny or stuffy nose?")
    sneezing = ask_question("Are you sneezing frequently?")
    return runny_or_stuffy_nose or sneezing


def diagnose_flu():
    body_aches = ask_question("Do you have body aches?")
    fatigue = ask_question("Do you feel tired or fatigued?")
    high_temperature = ask_question("Do you have a temperature above 38°C?")
    return body_aches and fatigue and high_temperature


def diagnose_strep_throat():
    sore_throat = ask_question("Do you have a sore throat?")
    swollen_tonsils = ask_question("Are your tonsils swollen?")
    return sore_throat and swollen_tonsils


def diagnose_food_poisoning():
    nausea = ask_question("Do you feel nauseous?")
    vomiting = ask_question("Have you been vomiting?")
    diarrhea = ask_question("Do you have diarrhea?")
    return nausea and vomiting and diarrhea


def diagnose_appendicitis():
    severe_abdominal_pain = ask_question("Do you have severe abdominal pain?")
    loss_of_appetite = ask_question("Have you lost your appetite?")
    return severe_abdominal_pain and loss_of_appetite


def main():
    print("\nWelcome to the Expert System for Medical Diagnosis\n")

    has_allergies = diagnose_allergies()
    has_fever = diagnose_fever()
    has_cold = diagnose_cold()
    has_flu = diagnose_flu()
    has_strep_throat = diagnose_strep_throat()
    has_food_poisoning = diagnose_food_poisoning()
    has_appendicitis = diagnose_appendicitis()

    print("\nDiagnosis:")
    if has_allergies:
        print("You may have allergies.")
    if has_fever:
        print("You may have a fever.")
    if has_cold:
        print("You may have a cold.")
    if has_flu:
        print("You may have flu.")
    if has_strep_throat:
        print("You may have a throat infection.")
    if has_food_poisoning:
        print("You may have food poisoning.")
    if has_appendicitis:
        print("You may have appendicitis.")

    # if none of the conditions are met
    if not any([has_allergies, has_fever, has_cold, has_flu, has_strep_throat, has_food_poisoning, has_appendicitis]):
        print("No specific diagnosis could be made based on the provided symptoms.")


main()