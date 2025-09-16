#include "../../includes/ast.h"

int type_pipe_error_and_return(void)
{
    perror("pipe failed");
    return (1);
}