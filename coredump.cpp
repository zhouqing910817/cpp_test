#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <string.h>

ssize_t get_uprobe_offset(const void *addr)
{
	size_t start, end, base;
	char buf[256];
	bool found = false;
	FILE *f;

	f = fopen("/proc/self/maps", "r");
	if (!f)
		return -errno;

	while (fscanf(f, "%zx-%zx %s %zx %*[^\n]\n", &start, &end, buf, &base) == 4) {
		if (buf[2] == 'x' && (uintptr_t)addr >= start && (uintptr_t)addr < end) {
			found = true;
            std::cout << "target line: " << buf << std::endl;
			break;
		}
	}

	fclose(f);

	if (!found)
		return -ESRCH;

	return (uintptr_t)addr - start + base;
}

int add(int a, int b) {
    std::shared_ptr<char> ptr;
    std::cout << *ptr << std::endl;
    return a + b;
}

int main(int argc, char** argv) {
    std::shared_ptr<char> ptr;
    strlen(ptr.get());
    printf("%p\n", &add);
    int off_set = get_uprobe_offset((void*)&add);
    std::cout << "add off_set: " << off_set << std::endl;
    int ret = add(1 , 2);
    std::cout << *ptr << ret << std::endl;
    return 0;
}
