#include "mystring.h"

#include <cstring>
#include <iostream>
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
	splay(temp_pointer, nullptr);
}

char * My_string::c_str()
{
	stack<string_node_pointer> st;

	char* temp_s = new char[length()];
	memset(temp_s, 0, sizeof(char));
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
	return temp_s;
}

void My_string::test()
{
	add_char('c');
	add_char('a');
	add_char('d');
	add_char('s');
	char *c = c_str();
	puts(c);
}


int main()
{
	My_string str;

	int n;
	cout << str.length() << endl;

	str.test();

	cin >> n;

	return 0;
}