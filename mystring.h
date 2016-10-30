#ifndef __MY_STRING_H_
#define __MY_STRING_H_

#define string_node_pointer My_string_node*

typedef unsigned int size_type;

#define DEBUG

class My_string_node {
public:

	My_string_node();
	My_string_node(const char& temp_char);

	inline string_node_pointer left() { return __left_node; }
	inline string_node_pointer right() { return __right_node; }
	inline string_node_pointer father() { return __father_node; }

	inline void set_left(string_node_pointer temp_pointer) { __left_node = temp_pointer; }
	inline void set_right(string_node_pointer temp_pointer) { __right_node = temp_pointer; }
	inline void set_father(string_node_pointer temp_pointer) { __father_node = temp_pointer; }

	inline void set_head() { __is_head = true; __size = 0; }
	inline void set_tail() { __is_tail = true; __size = 0; }
	
	inline size_type size() { return __size; }

	inline char c()const { return __char; }
	inline void set_char(const char& temp_c) { __char = temp_c; }

	inline bool is_special() { return __is_tail || __is_head; }

	inline void update()
	{
		__size = is_special();
		if (__left_node != nullptr) __size += __left_node->size();
		if (__right_node != nullptr)__size += __right_node->size();
	}

private:
	string_node_pointer  __left_node;
	string_node_pointer __right_node;
	string_node_pointer __father_node;

	bool __is_tail;
	bool __is_head;

	char __char;

	size_type __size;
};

class My_string {

public:

	My_string();

	void rotate(string_node_pointer current_node);
	void splay(string_node_pointer current_node, string_node_pointer splay_position);
	inline size_type length() { return __root_node->size(); }
	void add_char(const char& insert_char);

	char* c_str();

#ifdef DEBUG

	void test();

	
#endif 


private:

	inline string_node_pointer new_string_node(char temp_char = '\0')
	{
		string_node_pointer temp_pointer;
		temp_pointer = new My_string_node;
		temp_pointer->set_char(temp_char);
		return temp_pointer;
	}

	string_node_pointer __root_node;
	string_node_pointer __head_node;
	string_node_pointer __tail_node;

};

#endif