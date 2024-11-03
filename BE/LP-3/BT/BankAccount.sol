pragma solidity ^0.8.0;

contract Bank {

    // stores user balance as INT against the user address
    mapping(address => uint) balance;

    // function to deposit money
    function deposit() public payable {
        balance[msg.sender] = balance[msg.sender] + msg.value;
    }

    // function to withdraw money
    function withdraw(uint amount) public {
        require(amount <= balance[msg.sender], "Insufficient balance.");
        balance[msg.sender] = balance[msg.sender] - amount;

        // meaning = the sender is payable the amount mentioned
        payable(msg.sender).transfer(amount);
    }

    // function to check balance
    function checkBalance() public view returns(uint) {
        return balance[msg.sender];
    }
}
