#include "spdk/env.h"
#include "spdk/event.h"
#include "spdk/log.h"

//the application entry point by the reactor
//once here, we are running in user_space bypasing the kernel
static void app_start(void *arg1){
  //spdk structural logging
  spdk_log_set_print_level(SPDK_LOG_NOTICE);
  SPDK_NOTICELOG("SUCCESS: we are inside the spdk reactor loop!\n");

  //this is an infinite while poll-loop until we tell it to stop 
  spdk_app_stop(0); //this tells the scheduler to break the loop 

}
int main(int argc, char *argv[])
{
  struct spdk_app_opts opts={};
  int rc;

  //init the options structure wih spdk's default settings 
  spdk_app_opts_init(&opts, sizeof(opts));
  opts.name="basic_reactor";

  //parse standard cmd-line arguments eg core masks if passed 
  rc=spdk_app_parse_args(argc,argv, &opts, NULL,NULL,NULL,NULL);
  if (rc != SPDK_APP_PARSE_ARGS_SUCCESS) {
    return rc;
  
  }
  //this blocks the main thread , initializes hugepages , binds to CPU cores 
  //and hands execution off to our app_start function 
  rc=spdk_app_start(&opts,app_start, NULL);
  //clean up memory 
  spdk_app_fini();
  return rc;
}
