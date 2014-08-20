#include "QuestionMenu.hpp"
#include <boost/format.hpp>


QuestionMenu::QuestionMenu() : count_(0) {}
QuestionMenu::~QuestionMenu() {}
void QuestionMenu::add(Question::ConstPtr q)
{
  QuestionTable::iterator qit = groups_.find(q->cac_name);
  if(qit!=groups_.end())
  {
    qit->second.push_back(q);
  }
  else
  {
    QuestionList qs;
    qs.push_back(q);
    groups_[q->cac_name] = qs;
  }
  count_++;
}
void QuestionMenu::display(const CACMap& cac_map)
{
  list_.clear();
  int i=0;
  QuestionTable::iterator qg_it = groups_.begin();
  for(;qg_it!=groups_.end();++qg_it)
  {
    // display cac
    CACMap::const_iterator cac_entry = cac_map.find(qg_it->first);
    cout << cac_entry->second->desc << endl;
    QuestionList::const_iterator q_it = qg_it->second.begin();
    // list questions
    for(;q_it!=qg_it->second.end();++q_it)
    {
      string q_str = boost::str(boost::format("\t%d. %s") % (i+1) % (*q_it)->text );
      cout << q_str << endl;
      list_.push_back(*q_it);
      i++;
    }
  }
}
Question::ConstPtr QuestionMenu::select(size_t index)
{
  assert(count_==list_.size());
  assert(index <= count_);
  return list_.at(index-1);
}

bool QuestionMenu::empty() { return count_==0; }
size_t QuestionMenu::size() { return count_; }
