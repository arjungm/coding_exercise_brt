#include "Browser.hpp"
#include <boost/make_shared.hpp>
#include <sstream>
#include <fstream>
#include <cassert>

SystemBrowser::SystemBrowser() :
cacs_(),
questions_(),
stories_(),
question_to_story_(),
default_story_(),
system_name_(""),
system_id_("")
{
}

SystemBrowser::~SystemBrowser()
{
}

void SystemBrowser::run()
{
  Story::ConstPtr s = default_story_;

  cout << s->title << endl;
  cout << s->text << endl;

  while(true)
  {
    // ask the questions
    QuestionMenu menu;
    getRaisedQuestions( *s, menu );

    if(menu.empty())
    {
      cout << "***RESET***" << endl;
      s=default_story_;
      cout << s->title << endl;
      cout << s->text << endl;
      continue;
    }
    menu.display(cacs_);
    
    // block for user input  
    int option = getValidInput( (int)menu.size() );
    cout << "==================================" << endl;
    if(option < 0)
      break;

    // get selected question
    Question::ConstPtr qi = menu.select(option);
    
    // get answer
    QuestionToStoryMap::iterator qs_pair =  question_to_story_.find(qi->id);
    if(qs_pair==question_to_story_.end())
    {
      s = default_story_;
    }
    else
    {
      int s_id = qs_pair->second;
      if(s_id < 0)
        s = default_story_;
      else
        s = stories_[ s_id ];
    }
    cout << s->title << endl;
    cout << s->text << endl;
  }
}

int SystemBrowser::getValidInput(int max_options)
{
  string input;
  while(true)
  {
    cout << "Enter a number and hit [Enter]: ";
    getline(cin, input);
    if(input.length()==1 && input=="q")
      return -1;
    
    int option; 
    stringstream ss(input);
    if( !(ss >> option) )
      continue;
    
    if( !(0<option && option<=max_options) )
      continue; 
    return option;
  }
}

void SystemBrowser::getRaisedQuestions(const Story& s, QuestionMenu& menu)
{
  for(vector<int>::const_iterator i=s.questions_raised.begin();i!=s.questions_raised.end();++i)
  {
    QuestionMap::iterator q_it = questions_.find(*i);
    if(q_it!=questions_.end())
      menu.add( q_it->second );
  }
}

void SystemBrowser::loadFromFile(const string& file)
{
  std::ifstream in(file.c_str());
  SExprReader reader(in);
  SExprObject* obj;

  reader.read(&obj);
  while (obj != NULL)
  {
    if( obj->get_type() == SExprObject::TYPE_LIST )
    {
      ObjectType obj_parse_type = identifySExprObjectByName( **(obj->get_list().begin()) );
      switch(obj_parse_type)
      {
        case NO_TYPE:
          {
            //TODO
            break;
          }
        case QUESTION_TYPE:
          {
            Question::Ptr q = boost::make_shared<Question>();
            parseQuestionFromObject(*obj,*q);
            questions_[q->id] = q;
            break;
          }
        case ASK_TYPE:
          {
            parseSystemFromObject(*obj);
            break;
          }
        case STORY_TYPE:
          {
            Story::Ptr s = boost::make_shared<Story>();
            parseStoryFromObject(*obj,*s);
            if(s->id<0)
              default_story_ = s;
            else
              stories_[s->id] = s;
            break;
          }
        case CAC_TYPE:
          {
            CAC c;
            parseCACFromObject(*obj,c);
            cacs_[c.name] = c;
            break;
          }
      }
    }

    delete obj;
    reader.read(&obj);
  }
}

SystemBrowser::ObjectType SystemBrowser::identifySExprObjectByName(const SExprObject& obj)
{
  string def_type;
  if(obj.get_type() == SExprObject::TYPE_SYMBOL)
    def_type = obj.get_symbol_name();

  if(def_type == "def-cac-link")
    return CAC_TYPE;
  if(def_type == "def-question")
    return QUESTION_TYPE;
  if(def_type == "def-story")
    return STORY_TYPE;
  if(def_type == "def-ask-system")
    return ASK_TYPE;

  return NO_TYPE;
}

void SystemBrowser::vectorizeObject(const SExprObject& obj, vector<SExprObject*>& olist)
{
  assert( obj.get_type() == SExprObject::TYPE_LIST );
  olist.clear();
  const SExprObject::SExprObjectList& list = obj.get_list();
  for (SExprObject::SExprObjectList::const_iterator i = list.begin(); i != list.end(); i++)
    olist.push_back(*i);
}

void SystemBrowser::parseQuestionFromObject(const SExprObject& obj, Question& q)
{
  vector<SExprObject*> list;
  vectorizeObject(obj, list);

  assert(list.size()==5);
  assert(list[0]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[0]->get_symbol_name() == "def-question");
  assert(list[1]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[2]->get_type() == SExprObject::TYPE_NUMBER);
  assert(list[3]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[4]->get_type() == SExprObject::TYPE_STRING);

  q.sys_name = list[1]->get_symbol_name();
  q.id = list[2]->get_number();
  q.cac_name = list[3]->get_symbol_name();
  q.text = list[4]->get_string();
}

void SystemBrowser::parseCACFromObject(const SExprObject& obj, CAC& c)
{
  vector<SExprObject*> list;
  vectorizeObject(obj, list);

  assert(list.size()==4);
  assert(list[0]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[0]->get_symbol_name() == "def-cac-link");
  assert(list[1]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[2]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[3]->get_type() == SExprObject::TYPE_STRING);
  
  c.sys_name = list[1]->get_symbol_name();
  c.name = list[2]->get_symbol_name();
  c.desc = list[3]->get_string();
}

void SystemBrowser::parseStoryFromObject(const SExprObject& obj, Story& s)
{
  vector<SExprObject*> list;
  vectorizeObject(obj, list);

  assert(list.size()>=6);
  assert(list[0]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[0]->get_symbol_name() == "def-story");

  bool default_story = false;
  if(list.size()==6)
    default_story = true;

  if(default_story)
  {
    assert(list[1]->get_type() == SExprObject::TYPE_SYMBOL);
    assert(list[2]->get_type() == SExprObject::TYPE_STRING);
    assert(list[3]->get_type() == SExprObject::TYPE_LIST);
    assert(list[4]->get_type() == SExprObject::TYPE_LIST);
    assert(list[5]->get_type() == SExprObject::TYPE_STRING);

    s.id = -1;
    s.title = list[2]->get_string();
    s.text = list[5]->get_string();

    getNumberList( *(list[3]), s.questions_raised);
    getNumberList( *(list[4]), s.questions_answered);
  }
  else
  {
    assert(list[1]->get_type() == SExprObject::TYPE_SYMBOL);
    assert(list[2]->get_type() == SExprObject::TYPE_NUMBER);
    assert(list[3]->get_type() == SExprObject::TYPE_STRING);
    assert(list[4]->get_type() == SExprObject::TYPE_LIST);
    assert(list[5]->get_type() == SExprObject::TYPE_LIST);
    assert(list[6]->get_type() == SExprObject::TYPE_STRING);

    s.id = list[2]->get_number();
    s.title = list[3]->get_string();
    s.text = list[6]->get_string();

    getNumberList( *(list[4]), s.questions_raised);
    getNumberList( *(list[5]), s.questions_answered);
  }
  
  s.sys_name = list[1]->get_symbol_name();
  for(int i=0; i<(int)s.questions_answered.size(); ++i)
    question_to_story_[ s.questions_answered[i] ] = s.id;
}

void SystemBrowser::parseSystemFromObject(const SExprObject& obj)
{
  vector<SExprObject*> list;
  vectorizeObject(obj, list);

  assert(list.size()==3);
  assert(list[0]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[0]->get_symbol_name() == "def-ask-system");
  assert(list[1]->get_type() == SExprObject::TYPE_SYMBOL);
  assert(list[2]->get_type() == SExprObject::TYPE_STRING);
  
  system_id_ = list[1]->get_symbol_name();
  system_name_ = list[2]->get_string();
}

void SystemBrowser::getNumberList(const SExprObject& obj, vector<int>& list)
{
  list.clear();
  vector<SExprObject*> num_list;
  vectorizeObject(obj, num_list);
  for(vector<SExprObject*>::iterator i=num_list.begin(); i!=num_list.end(); ++i)
    list.push_back( (*i)->get_number() );
}

void SystemBrowser::printThings(const string& sys_name, int i)
{
  QuestionMap::iterator qit = questions_.begin();
  for(;qit!=questions_.end();++qit)
  {
    if(sys_name == qit->second->sys_name && i==qit->second->id)
    {
      string out = boost::str(boost::format("Question: %s") % qit->second->text);
      cout << out << endl;
    }
  }
}
