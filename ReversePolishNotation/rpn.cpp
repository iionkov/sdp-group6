//Това се примерни решения, възможни са и други реализации.
#include <iostream>
#include <stack>
using namespace std;
//Помощна функция, връщаща броя на скобите в един запис. 
int numOfBraces(const char* s) {
	int res = 0;
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == '(' || s[i] == ')') res++;
	return res;
}
//Първи начин
//Помощна функция, отразяваща приоритета на операциите.
int first_priority(char ch) {
	switch (ch) {
	case '+': return 1; break;
	case '-': return 1; break;
	case '*': return 2; break;
	case '/': return 2; break;
	case '^': return 3; break;
	default: return -1; break;
	}
}
//Първа примерна функция, която приема обикновен израз и го преобразува в обратен полски.
const char* first_translate(char*s) {
	char*ns=new char[strlen(s)+1-numOfBraces(s)];
	int i = 0, j = 0;
	stack<char>op;
	char c;
	op.push('(');
	while (i < strlen(s)) {
		if (s[i] >= '0' && s[i] <= '9') {
			ns[j++] = s[i];
		}
		else if (s[i] == '(') {
			op.push('(');
		}
		else if (s[i] == ')') {
			c = op.top();
			while (c != '(') {
				op.pop();
				ns[j++] = c;
				c = op.top();
			}
		}
		else {
			c = op.top();
			while (c != '(' && priority(c) >= priority(s[i])) {
				ns[j++] = c;
				op.pop();
				c = op.top();
			}
			op.push(s[i]);
		}
		i++;
	}
	c = op.top();
	while (c != '(') {
		ns[j++] = c;
		op.pop();
		c =op.top();
	}
	ns[j] = '\0';
	return ns;
}
//Втори начин
//Помощна функция, отразяваща приоритета на операциите.
int second_priority(char ch) {
	switch (ch) {
	case '(': return 0; break;
	case '+': return 1; break;
	case '-': return 1; break;
	case '*': return 2; break;
	case '/': return 2; break;
	case '^': return 3; break;
	default: return -1; break;
	}
}
//Втора примерна функция, която приема обикновен израз и го връща в обратен полски.
const char* second_translate(char* s) {
	char* ns = new char[strlen(s) + 1 - numOfBraces(s)];
	stack<char> op;
	int i = 0, j = 0, n = strlen(s);
	while (i < n) {
		if (s[i] >= '0' && s[i] <= '9') ns[j++] = s[i];
		else if (s[i] == '(') op.push(s[i]);
		else if (s[i] == ')') {
			while (op.top() != '(') {
				ns[j++] = op.top();
				op.pop();
			}
			op.pop();
		}
		else {
			while (!op.empty() && priority(op.top()) >= priority(s[i])) {
				ns[j++] = op.top();
				op.pop();
			}
			op.push(s[i]);
		}
		i++;
	}
	while (!op.empty()) {
		ns[j++] = op.top();
		op.pop();
	}
	ns[j] = '\0';
	return ns;
}
//Пресмятане на стойност по подаден обратен полски запис.
int value(const char* s) {
	stack<int> st;
	int i = 0, first, second;
	while (i < strlen(s)) {
		if (s[i] >= '0' && s[i] <= '9') st.push(s[i] - '0');
		else {
			second = st.top();
			st.pop();
			first = st.top();
			st.pop();
			switch (s[i]) {
				case '+': st.push(first + second); break;
				case '-': st.push(first - second); break;
				case '*': st.push(first * second); break;
				case '/': st.push(first / second); break;
				case '^': st.push(pow(first,second)); break;
			}
		}
		i++;
	}
	return st.top();
}
int main() {
  //cout << translate("3+(4+6)/2")<<endl; --> 346+2/+
  //cout<<value(translate("(7-2+4)^2"))<<endl; --> 81
	system("pause");
	return 0;
}
