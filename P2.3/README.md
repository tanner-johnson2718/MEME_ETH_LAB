# BCM Genet MAC Driver

* driver is bcmgenet at 'drivers/net/ethernet/broadcom/genet/*'
* First Look over, possible vectors of approaching this:
    * TX / RX Queues and ring buffers
    * DMA
    * Stat vectors / registers / etc
    * ACPI?
    * Kernel memory allocation