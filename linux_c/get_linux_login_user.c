#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
 
int main(const int argc, const char** argv)
{
    struct passwd *pwd = getpwuid(getuid());
    printf("login account：%s\n", pwd->pw_name);
 
    //free(pwd); 
	//pwd = NULL;
    return 0;
}
