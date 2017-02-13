import random
target = open("test_new.txt",'w')
string = "abcdefghijklmnopqrstuvwxyzabcdef !@#$%^&*()1234567890><>:{}|?,.;[]"
for i in range(100000):
	str = ""
	for j in range(300):
		num = random.randint(0,65)
		str += string[num];
	target.write(str + "\n");
target.close();
