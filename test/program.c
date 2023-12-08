#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
 /*
int main()
{
	int	fd;
	char	*buf;
	int	chars_read;
	int	i;
	
	fd = open("file.txt", O_RDONLY);
	printf("%d\n", fd);
	buf = (char *)malloc((100) * sizeof(char));
	if(!buf)
		return (0);
	buf[chars_read] = '\0';
	i = 0;
	chars_read = read(fd, buf, 99);
	while(buf[i] != '\0')
		write(1, &buf[i++], 1);
	free(buf);
	printf("\n seconda chiamata : \n");
	buf = (char *)malloc((11) * sizeof(char));
	if(!buf)
		return (0);
	buf[10] = '\0';
	i = 0;
	chars_read = read(fd, buf, 10);
	while(buf[i] != '\0')
		write(1, &buf[i++], 1);
	free(buf);
	close(fd);
	return 0;
}
*/

void	test_static()
{
	static int a = 0;
	int b = 0;
	printf("a : %d\n", a++);
	printf("b : %d\n", b++);
}

int	main()
{
	int	i;
	
	i = 0;
	while(i++ < 10)
		test_static();
}
