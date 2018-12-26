/*****************************************************************************/
/*!
\file motoxrename.cpp
\author Connor Deakin
\par E-mail: connortdeakin\@gmail.com
\par Project: MotoXPictureVideoRenamer
\date 16/08/2017
\brief
  Does the job that is described in README.md.
*/
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstdio>

/*****************************************************************************/
/*!
\brief
  Just tests for string equality.

\return True if equal.
*/
/*****************************************************************************/
bool equal(const std::string & first, const std::string & second)
{
  if(first.size() != second.size())
    return false;
  unsigned size = first.size();
  for(unsigned i = 0; i < size; ++i){
    if(first[i] != second[i])
      return false;
  }
  return true;
}

/*****************************************************************************/
/*!
\brief
  Opens a directory and renames all files as described in README.md.
*/
/*****************************************************************************/
int main(int argc, char * argv[])
{
  // Checking for input error
  if(argc != 2){
    std::cout << "Include the directory name.";
    return 0;
  }
  std::string dir_name(argv[1]);
  unsigned last_char = dir_name.size() - 1;
  if(dir_name[last_char] == '/'){
    std::cout << "Don't include ending '/'";
    return 0;
  }
  // opening dir and reading all original file names
  DIR * image_dir;
  std::vector<std::string> original_names;
  image_dir = opendir(dir_name.c_str());
  if(image_dir != NULL)
  {
    dirent * dir_entry = NULL;
    dir_entry = readdir(image_dir);
    while(dir_entry != NULL)
    {
      if(dir_entry->d_name[0] == '.'){
        dir_entry = readdir(image_dir);
        continue;
      }
      original_names.push_back(std::string(dir_entry->d_name));
      dir_entry = readdir(image_dir);
    }
  }
  else
  {
    std::cout << "Dir open failed" << std::endl;
  }
  // extracting data from old names
  std::vector<std::string> new_names;
  std::vector<std::string>::const_iterator cit = original_names.begin();
  std::vector<std::string>::const_iterator cit_e = original_names.end();
  for(; cit != cit_e; ++cit)
    new_names.push_back(cit->substr(4,8));
  // adding number extension to new names
  std::vector<std::string>::iterator it = new_names.begin();
  std::vector<std::string>::iterator it_e = new_names.end();
  while(it != it_e){
    std::string cur_date(*it);
    it->append("_0");
    ++it;
    int date_num = 1;
    while(it != it_e && equal(*it, cur_date)){
      char number_extension[5];
      sprintf(number_extension, "_%d", date_num);
      it->append(number_extension);
      ++date_num;
      ++it;
    }
  }
  // adding hyphens and file extensions to new names
  cit = original_names.begin();
  cit_e = original_names.end();
  it = new_names.begin();
  it_e = new_names.end();
  for(; it != it_e && cit != cit_e; ++it, ++cit){
    it->insert(6,1,'-');
    it->insert(4,1,'-');
    size_t file_ext_start = cit->rfind('.');
    it->append(cit->substr(file_ext_start, cit->size() - file_ext_start));
  }
  // renaming all files in directory
  cit = original_names.begin();
  cit_e = original_names.end();
  it = new_names.begin();
  it_e = new_names.end();
  for(; it != it_e && cit != cit_e; ++it, ++cit){
    std::string original_name(dir_name);
    std::string new_name(dir_name);
    original_name.append(1, '/');
    original_name.append(*cit);
    new_name.append(1, '/');
    new_name.append(*it);
    int result = std::rename(original_name.c_str(), new_name.c_str());
    std::cout << original_name << " -> " << new_name;
    if(result)
      std::cout << " - FAILURE" << std::endl;
    else
      std::cout << " - S" << std::endl;
  }
  return 0;
}
