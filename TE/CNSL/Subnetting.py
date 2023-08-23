
class Subnetting:

    def __init__(self):
        self.ip = ''
        self.cidr = 0
        self.powerNumber = 0
        self.subnetMask = ''

    def getPowerNumber(self):
        return self.powerNumber

    def setPowerNumber(self):
        mod = self.cidr % 8
        self.powerNumber = 2**(8-mod)

    def getSubnets(self):
        return 256 // self.powerNumber
    

    def read(self):
        self.ip = input("Enter IP Address: ")
        ipList = self.ip.split(".", 4)

        for val in ipList:
            num = int(val)
            if (num < 0) or (num > 255):
                print("Invalid IP!")
                exit(1)

        self.cidr = int(input("Enter CIDR: "))
        if (self.cidr < 16) or (self.cidr > 31):
            print("Invalid CIDR!")
            exit(1)


    def find(self):
        is_supernetting = False

        if (self.cidr // 8) < 3:
            is_supernetting = True
        
        self.setPowerNumber()

        host = 256 - self.getPowerNumber()
        self.subnetMask = '255.255.'

        if is_supernetting:
            self.subnetMask += str(host) + '.0'
            print("Number of supernets formed:", self.getSubnets())
        else:
            self.subnetMask += '255.' + str(host)
            print("Number of subnets formed:", self.getSubnets())

        test = self.ip.split(".", 4)
        lastBits= int(test[2]) if is_supernetting else int(test[3])

        if is_supernetting:
            del test[2:4]
        else:
            del test[3]
        
        print("Subnet Mask: ", self.subnetMask)

        halfip = ".".join(test) + "."
        power = self.getPowerNumber()
        maxLimit = power
        minLimit = 0

    """
        while 256 >= maxLimit:
            if is_supernetting:
                print(f"{halfip}{minLimit}.0 to {halfip}{maxLimit - 1}.0", end="")
            else:
                print(f"{halfip}{minLimit} to {halfip}{maxLimit - 1}", end="")
                

            if minLimit < lastBits and maxLimit > lastBits:
                print(" <--- ip belongs to this range")
            else:
                print()
        
            minLimit = maxLimit
            minLimit += self.powerNumber
    """


obj = Subnetting()
obj.read()
obj.find()
