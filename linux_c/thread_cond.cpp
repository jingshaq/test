#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node {
	int n_number;
	struct node *n_next;
};
struct node *head = NULL;

static void cleanup_handler(void *arg)
{
	printf("clean sub thread.\n");
	if(arg != NULL)
	{
		free(arg);
	}
	pthread_mutex_unlock(&mtx);
}

static void *thread_func(void *arg)
{
	struct node *p = NULL;

	pthread_cleanup_push(cleanup_handler, p); //注册线程退出清理函数
	printf("sub thread start\n");
	while (1) {
		pthread_mutex_lock(&mtx);             //临界区数据操作完毕，释放互斥锁
		while (head == NULL)   {
			/*这个while要特别说明一下，单个pthread_cond_wait功能很完善，为何这里要有一个while (head == NULL)呢？
			 * 因为pthread_cond_wait里的线程可能会被意外唤醒，如果这个时候head != NULL，则不是我们想要的情况。
			 * 这个时候，应该让线程继续进入pthread_cond_wait
			*/
			pthread_cond_wait(&cond, &mtx);/* pthread_cond_wait会先解除之前的pthread_mutex_lock锁定的mtx，然后阻塞在等待对列里休眠，
										      直到再次被唤醒（大多数情况下是等待的条件成立而被唤醒，
			                                  唤醒后，该进程会先锁定先pthread_mutex_lock(&mtx);，再读取资源 */
			printf("wait finished.");
		}
		p = head;
		head = head->n_next;
		printf("Got %d from queue \n", p->n_number);
		free(p);
		pthread_mutex_unlock(&mtx);             //临界区数据操作完毕，释放互斥锁
	}
	pthread_cleanup_pop(0);
	printf("sub thread stop\n");
	return 0;
}

int main(void)
{
	pthread_t tid;
	int i;
	struct node *p;
	int ret;

	ret = pthread_create(&tid, NULL, thread_func, NULL);
	if(ret < 0)
	{
		printf("create thread error.\n");
	}

	for (i = 0; i < 10; i++) 
	{
		p = (struct node *)malloc(sizeof(struct node));
		p->n_number = i;
		pthread_mutex_lock(&mtx);//需要操作head这个临界资源，先加锁
		p->n_next = head;
		head = p;
		pthread_cond_signal(&cond); //发送线程信号，唤醒线程
		pthread_mutex_unlock(&mtx); //解锁
		usleep(100); //等待子线程处理
	}
	printf("main thread stop, cancel sub thread.\n");
	pthread_cancel(tid); /*关于pthread_cancel，有一点额外的说明，它是从外部终止子线程，子线程会在最近的取消点，退出线程，
						   而在我们的代码里，最近的取消点肯定就是pthread_cond_wait()了。
						   关于取消点的信息，有兴趣可以google,这里不多说了*/
	pthread_join(tid, NULL); // 等待子线程结束
	printf("program finished -- exit\n");
	return 0;
}
