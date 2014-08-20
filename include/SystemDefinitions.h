#ifndef SYS_DEF_H
#define SYS_DEF_H

#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

struct Question
{
  typedef boost::shared_ptr<Question> Ptr;
  typedef boost::shared_ptr<Question const> ConstPtr;
  int id;
  string cac_name;
  string sys_name;
  string text;
};

struct CAC
{
  string name;
  string desc;
  string sys_name;
};

struct Story
{
  typedef boost::shared_ptr<Story> Ptr;
  typedef boost::shared_ptr<Story const> ConstPtr;
  int id;
  string title;
  string text;
  vector<int> questions_raised;
  vector<int> questions_answered;
  string sys_name;
};

typedef map<int, Question::ConstPtr> QuestionMap;
typedef map<int, Story::ConstPtr> StoryMap;
typedef map<string, CAC> CACMap;

#endif
