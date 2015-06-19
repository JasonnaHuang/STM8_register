/* STATUS.C file
 * Date:2015.6.9
 * Auth:Jason.H_{
 */

#include "status.h"
#include "stdlib.h"

context_status_t *status;

unsigned char Status_Init(void)
{
  status = (context_status_t *)calloc(1,sizeof(context_status_t));
  if(!(status))
    return 0;
  return 1;
}