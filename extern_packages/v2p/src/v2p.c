#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/memory.h>
#include <linux/kobject.h>

static unsigned long p_addr = 0;
static unsigned long v_addr = 0;

static ssize_t v2p_p_show(struct kobject* kobj, struct kobj_attribute *attr, char *buf);
static ssize_t v2p_p_store(struct kobject* kobj, struct kobj_attribute *attr, const char *buf, size_t count);
static ssize_t v2p_v_show(struct kobject* kobj, struct kobj_attribute *attr, char *buf);
static ssize_t v2p_v_store(struct kobject* kobj, struct kobj_attribute *attr, const char *buf, size_t count);

static struct kobject *v2p_p_kobj;
static struct kobject *v2p_v_kobj;
static struct kobj_attribute v2p_p_attr = __ATTR(p_addr, 0660, v2p_p_show, v2p_p_store);
static struct kobj_attribute v2p_v_attr = __ATTR(v_addr, 0660, v2p_v_show, v2p_v_store);

static ssize_t v2p_p_show(struct kobject* kobj, struct kobj_attribute *attr, char *buf)
{
    printk(KERN_INFO "v2p p_addr show\n");
    return 0;
}

static ssize_t v2p_p_store(struct kobject* kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk(KERN_INFO "v2p p_addr store\n");
    return 0;
}

static ssize_t v2p_v_show(struct kobject* kobj, struct kobj_attribute *attr, char *buf)
{
    printk(KERN_INFO "v2p v_addr show\n");
    return 0;
}

static ssize_t v2p_v_store(struct kobject* kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk(KERN_INFO "v2p v_addr store\n");
    return 0;
}

static int v2p_init(void)
{
    // unsigned long test = virt_to_phys((void *) 5);

    v2p_p_kobj = kobject_create_and_add("v2p_p", kernel_kobj);
    if(!v2p_p_kobj)
    {
        printk(KERN_INFO "v2p Failed to create kobj\n");
        return -1;
    }

    v2p_v_kobj = kobject_create_and_add("v2p_v", kernel_kobj);
    if(!v2p_p_kobj)
    {
        kobject_put(v2p_p_kobj);
        printk(KERN_INFO "v2p Failed to create kobj\n");
        return -1;
    }

    if(sysfs_create_file(v2p_p_kobj, &v2p_p_attr.attr))
    {    
        kobject_put(v2p_p_kobj);
        kobject_put(v2p_v_kobj);
        
        printk(KERN_INFO "v2p Cannot create sysfs file......\n");

        return -1;
    }

    if(sysfs_create_file(v2p_v_kobj, &v2p_v_attr.attr))
    {    
        sysfs_remove_file(v2p_p_kobj, &v2p_p_attr.attr);

        kobject_put(v2p_p_kobj);
        kobject_put(v2p_v_kobj);
        
        printk(KERN_INFO "v2p Cannot create sysfs file......\n");

        return -1;
    }

    printk(KERN_INFO "v2p Loaded\n");
    return 0;
}

static void v2p_exit(void)
{
    sysfs_remove_file(v2p_p_kobj, &v2p_p_attr.attr);
    sysfs_remove_file(v2p_v_kobj, &v2p_v_attr.attr);

    kobject_put(v2p_p_kobj);
    kobject_put(v2p_v_kobj);

    printk(KERN_INFO "v2p unLoaded\n");
}

module_init(v2p_init)
module_exit(v2p_exit)
MODULE_LICENSE("GPL");