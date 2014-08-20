#ifndef BROWSER_H
#define BROWSER_H

#include <map>
#include <string>
#include <iostream>
#include <vector>

#include "SystemDefinitions.h"
#include "QuestionMenu.hpp"
#include "SExprReader.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

using namespace std;


class SystemBrowser
{
  enum ObjectType
  {
    QUESTION_TYPE,
    CAC_TYPE,
    STORY_TYPE,
    ASK_TYPE,
    NO_TYPE
  };
  public:
    typedef map<int, int> QuestionToStoryMap;
    SystemBrowser();
    ~SystemBrowser();
    void loadFromFile(const string& file);
    void printThings(const std::string& system_name, int i);
    void run();
  
  protected:
    int getValidInput(int max_options);
    
    void getRaisedQuestions(const Story& s, QuestionMenu& menu);
    
    ObjectType identifySExprObjectByName(const SExprObject& obj);
    
    // useful parsing functions.
    void parseSystemFromObject(const SExprObject& obj);
    void parseQuestionFromObject(const SExprObject& obj, Question& q);
    void parseStoryFromObject(const SExprObject& obj, Story& s);
    void parseCACFromObject(const SExprObject& obj, CAC& c);
    void getNumberList(const SExprObject& obj, vector<int>& list);
    void vectorizeObject(const SExprObject& obj, vector<SExprObject*>& olist);

  private:
    CACMap cacs_;
    QuestionMap questions_;
    StoryMap stories_;
    QuestionToStoryMap question_to_story_;
    
    Story::ConstPtr default_story_;
    string system_name_;
    string system_id_;
};

#endif
