// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {

    struct Student {
        uint rollno;
        string name;
    }

    // array of Student structures
    Student[] public students;

    // mapping of Student structures
    mapping(uint => Student) studentMapping;

    // function to add student
    // string needs to be saved in the contract's memory during execution
    function addStudent (uint rollno, string memory name) public {
        students.push(Student(rollno, name));  // add to array
        studentMapping[rollno] = Student(rollno, name);  // add a mapping
    }

    // function to get student data using mapping
    function getStudent(uint _rollno) public view returns(uint rollno, string memory name) {
        return(studentMapping[_rollno].rollno, studentMapping[_rollno].name);
    }

    // alternative method with a for-loop using array
    function getStudent2(uint _rollno) public view returns(uint rollno, string memory name) {
        for (uint i=0; i<students.length; i++) {
            if (students[i].rollno == _rollno) {
                return(students[i].rollno, students[i].name);
            }
        }
        // if not found
        revert("Student not found.");
    }

    // fallback function is executed when a contract receives Ether along with a call to a function that does not exist or with incorrect parameters
    // make this function payable if there are Ether transactions
    fallback() external {
        revert("Invalid function call or Ether transfer not supported.");   
    }

    // to trigger the fallback function in Remix IDE:
    // scroll to the bottom of the deployed contracts tab and expand your contract
    // in the CALLDATA input field type: 0x12345678
    // click on TRANSACT, and check the terminal for reverted output
}
