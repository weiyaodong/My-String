#include "mystring.h"

#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

My_string_node:: My_string_node()
{
	__father_node = __left_node = __right_node = nullptr;
	__is_tail = __is_head = false;
	__size = 1;
	__char = 0;
}

My_string_node::My_string_node(const char & temp_char)
{
	__father_node = __left_node = __right_node = nullptr;
	__is_tail = __is_head = false;
	__size = 1;
	__char = temp_char;
}

My_string::My_string()
{
	__head_node = new_string_node();
	__head_node->set_head();
	__tail_node = new_string_node();
	__tail_node->set_tail();

	__head_node->set_right(__tail_node);
	__tail_node->set_father(__head_node);
	__root_node = __head_node;

}

My_string & My_string::operator=(const My_string & copy_string)
{
	clear();	
	return *this = copy_string.c_str();
}

My_string & My_string::operator = (char * c_string)
{
	clear();

	string_node_pointer* pointers;
	int __length = strlen(c_string);
	pointers = new string_node_pointer[__length+2];
	pointers[0] = new_string_node();
	pointers[0]->set_head();
	__root_node = __head_node = pointers[0];
	pointers[__length + 1] = new_string_node();
	pointers[__length + 1]->set_tail();
	__tail_node = pointers[__length + 1];
	for (int i = 1; i <= __length; i++)
	{
		pointers[i] = new_string_node(c_string[i - 1]);
	}
	for (int i = 0; i <= __length; i++)
	{
		pointers[i]->set_right(pointers[i + 1]);
		pointers[i + 1]->set_father(pointers[i]);
	}
	
	splay(__tail_node, nullptr);
	delete pointers;
	return *this;
}

void My_string::clear()
{
	queue<string_node_pointer> q;
	q.push(__root_node);
	while (!q.empty())
	{		
		string_node_pointer temp_pointer = q.front(); q.pop();

		if (temp_pointer == nullptr)
			continue;

		string_node_pointer temp_left = temp_pointer->left();
		string_node_pointer temp_right = temp_pointer->right();
		delete temp_pointer;
		if (temp_left != nullptr)
		{
			q.push(temp_left);
		}
		if (temp_right != nullptr)
		{
			q.push(temp_right);
		}
	}
	__head_node = __tail_node = __root_node = nullptr;
}

void My_string::rotate(string_node_pointer current_node)
{
	

	bool is_right_child = current_node->father()->right() == current_node;
	string_node_pointer father_node = current_node->father();

	if (father_node == __root_node)
	{
		__root_node = current_node;
	}

	if (is_right_child)
	{
		if (current_node->left() != nullptr)current_node->left()->set_father(father_node);
		father_node->set_right(current_node->left());
		current_node->set_left(father_node);
	}
	else
	{
		if (current_node->right() != nullptr)current_node->right()->set_father(father_node);
		father_node->set_left(current_node->right());
		current_node->set_right(father_node);
	}
	if (father_node->father() != nullptr)
	{
		bool is_right_child2 = father_node->father()->right() == father_node;
		if (is_right_child2) father_node->father()->set_right(current_node);
		else father_node->father()->set_left(current_node);
	}
	current_node->set_father(father_node->father());
	father_node->set_father(current_node);

	father_node->update();
	current_node->update();	
}

void My_string::splay(string_node_pointer current_node, string_node_pointer splay_position)
{
	while (current_node->father() != splay_position)
	{
		if (current_node->father()->father() == splay_position)
		{
			rotate(current_node);
			continue;
		}
		string_node_pointer father_node = current_node->father();
		string_node_pointer grandpa_node = father_node->father();
		if ((grandpa_node->right() == father_node) ^ (father_node->right() == current_node))
		{
			rotate(current_node);
		}
		else rotate(father_node);
		rotate(current_node);
	}

	if (splay_position == nullptr)
		__root_node = current_node;
}


void My_string::add_char(const char & insert_char)
{
	splay(__tail_node, nullptr);
	rotate(__tail_node->left());
	string_node_pointer temp_pointer = new_string_node(insert_char);
	__root_node->right()->set_left(temp_pointer);
	temp_pointer->set_father(__root_node->right());
	__root_node->right()->update();
	__root_node->update();
	splay(temp_pointer, nullptr);
}

My_string My_string::operator + (const char & add_char) const
{
	My_string temp_string;
	char *str;
	str = new char[this->length() + 2];
	strcpy(str, c_str());
	str[this->length()] = add_char;
	str[this->length() + 1] = '\0';
	temp_string = str;
	delete str;
	return temp_string;
}

My_string My_string::operator + (char* c_string) const
{
	My_string temp_string;
	char *str;
	size_type c_length = strlen(c_string);
	str = new char[this->length() + c_length + 1];
	strcpy(str, c_str());
	strcpy(str + this->length(), c_string);
	str[this->length() + c_length] = '\0';
	temp_string = str;
	delete str;
	return temp_string;
}

My_string My_string::operator + (const My_string& add_string) const
{
	My_string temp_string = *this;
	My_string temp_string2 = add_string;
	// to be continued 
}

char * My_string::c_str() const
{
	stack<string_node_pointer> st;

	int __length = __root_node->size();

	char* temp_s = new char[__length+1];


	memset(temp_s, '\0', sizeof(char));
	int counter = 0;
	string_node_pointer current_node = __root_node;

	while (!st.empty() || current_node != nullptr)
	{
		while (current_node != nullptr)
		{
			st.push(current_node);
			current_node = current_node->left();
		}
		if(!st.empty())
		{
			current_node = st.top(); 
			st.pop();
			if (!current_node->is_special())
				temp_s[counter++] = current_node->c();
			current_node = current_node->right();
		}
	}
	temp_s[__length] = '\0';
	return temp_s;
}

void My_string::test()
{
	add_char('c');
	add_char('a');
	add_char('d');
	add_char('s');
 
	puts(c_str());
}



int main()
{
	My_string str,str2;

	int n;
	cout << str.length() << endl;

	str.test();

	str = "string";
	puts(str.c_str());
	str2 = str;
	puts(str2.c_str());
	str = str2 + "string";
	puts(str.c_str());

	cin >> n;

	return 0;
}