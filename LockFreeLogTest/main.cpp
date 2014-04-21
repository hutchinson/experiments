#include <iostream>
#include <sstream>
#include <pthread.h>

extern "C"
{
void ReportMessage(const std::string &message, bool useCerr)
{
  std::stringstream ss;
  ss << message << "\n";
  std::string s(ss.str());

  if(useCerr)
  {
    std::cerr << s;
    std::cerr.flush();
  }
  else
  {
    std::cout << s;
    std::cout.flush();
  }
}
}
void* THREAD_FUNC(void *args)
{
  int tid = *((int*)args);

  bool useCerr = tid % 2;

  for(int x = 0; x < 100; ++x)
  {
    std::stringstream ss;
    ss << "TID[ "
       << tid
       << " ]  - Message "
       << x;
    std::string s(ss.str());

    ReportMessage(s, useCerr);
  }
}

struct thread_store
{
  pthread_t thread;
  int task_id;
};

thread_store THREADS[250];

int main(int argc, char **argv)
{
  // Uncomment this line to break things.
  // std::ios_base::sync_with_stdio(false);
  for(int task = 0; task < 250; ++task)
  {
    THREADS[task].task_id = task;
    pthread_create(&THREADS[task].thread, 0, THREAD_FUNC, &THREADS[task].task_id);
  }

  for(int task = 0; task < 250; ++task)
  {
    pthread_join(THREADS[task].thread, NULL);
  }

  std::cout << "Complete" << std::endl;

  return 0;
}
