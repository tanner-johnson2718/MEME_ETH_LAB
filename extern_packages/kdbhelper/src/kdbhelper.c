#include <linux/module.h>
#include <linux/kdb.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp_kln = 
{
    .symbol_name = "kallsyms_lookup_name",
};

/*
 * All kdb shell command call backs receive argc and argv, where
 * argv[0] is the command the end user typed
 */
static int kdb_hello_cmd(int argc, const char **argv)
{
	if (argc > 1)
		return KDB_ARGCOUNT;

	if (argc)
		kdb_printf("Hello %s.\n", argv[1]);
	else
		kdb_printf("Hello world!\n");

	return 0;
}

static int kdb_symbol_name_search(int argc, const char **argv)
{
    if (! (argc == 2))
    {
        return KDB_ARGCOUNT;   
    }
    
    // unsigned long addr = kallsyms_lookup_name(argv[1]);
    // kdb_printf("%s resolves to %lx\n", argv[1], addr);

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

	kdb_register("hello", kdb_hello_cmd, "[string]",
		     "Say Hello World or Hello [string]", 0);

    kdb_register("sym_to_addr", kdb_symbol_name_search, "[string]",
                 "Search for addr of kernel symbol", 3);

    if(register_kprobe(&kp_kln))
    {
        pr_info("kallsyms_lookup_name kprobe failed\n");
        return -1;
    }

    pr_info("kallsyms_lookup_name: %px\n", kp_kln.addr);

	return 0;
}

static void __exit kdb_hello_cmd_exit(void)
{
    pr_info("KDB Helper Unlaoded\n");

	kdb_unregister("hello");
    kdb_unregister("sym_to_addr");

    unregister_kprobe(&kp_kln);
}

module_init(kdb_hello_cmd_init);
module_exit(kdb_hello_cmd_exit);

MODULE_AUTHOR("WindRiver");
MODULE_DESCRIPTION("KDB example to add a hello command");
MODULE_LICENSE("GPL");
