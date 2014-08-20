#ifndef QUESTION_MENU_H
#define QUESTION_MENU_H
#include "SystemDefinitions.h"
#include <vector>

using namespace std;

class QuestionMenu
{
  public:
    typedef vector<Question::ConstPtr> QuestionList;
    typedef map<string, vector<Question::ConstPtr> > QuestionTable;
    QuestionMenu();
    ~QuestionMenu();
    void add(Question::ConstPtr q);
    void display(const CACMap& cac_map);
    Question::ConstPtr select(size_t index);
    bool empty();
    size_t size();
  private:
    QuestionTable groups_;
    QuestionList list_;
    size_t count_;
};
#endif
