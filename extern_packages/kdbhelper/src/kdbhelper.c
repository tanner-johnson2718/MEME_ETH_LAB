#include <linux/module.h>
#include <linux/kdb.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/string.h>

unsigned long (*kln_pointer)(const char *name) = NULL;
static char str_buffer[64] = "kallsyms_lookup_name";
static struct kprobe kp = {
    .symbol_name = str_buffer,
};

static int kdb_symbol_name_search(int argc, const char **argv)
{
    if (! (argc == 1))
    {
        return KDB_ARGCOUNT;   
    }
    
    kdb_printf("%s -> 0x%lx\n", argv[1], kln_pointer(argv[1]));

    return 0;
}

static int __init kdb_hello_cmd_init(void)
{
	/*
	 * Registration of a dynamically added kdb command is done with
	 * kdb_register() with the arguments being:
	 *   1: The name of the shell command
	 *   2: The function that processes the command
	 *   3: Description of the usage of any arguments
	 *   4: Descriptive text when you run help
	 *   5: Number of characters to complete the command
	 *      0 == type the whole command
	 *      1 == match both "g" and "go" for example
	 */

    pr_info("KDB Helper Loading\n");

    kdb_register("addr", kdb_symbol_name_search, "[string]",
                 "Search for addr of kernel symbol", 0);

    if(register_kprobe(&kp))
    {
        pr_info("done goofed on register probe\n");
        return -1;
    }

    kln_pointer = (long unsigned int (*)(const char *)) kp.addr;

    unregister_kprobe(&kp);

	return 0;
}

static void __exit kdb_hello_cmd_exit(void)
{
    pr_info("KDB Helper Unloaded\n");
    kdb_unregister("addr");
}

module_init(kdb_hello_cmd_init);
module_exit(kdb_hello_cmd_exit);

MODULE_AUTHOR("WindRiver");
MODULE_DESCRIPTION("KDB example to add a hello command");
MODULE_LICENSE("GPL");
