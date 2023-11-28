struct bcmgenet_rx_ring {
	struct napi_struct napi;	/* Rx NAPI struct */
	unsigned long	bytes;
	unsigned long	packets;
	unsigned long	errors;
	unsigned long	dropped;
	unsigned int	index;		/* Rx ring index */
	struct enet_cb	*cbs;		/* Rx ring buffer control block */
	unsigned int	size;		/* Rx ring size */
	unsigned int	c_index;	/* Rx last consumer index */
	unsigned int	read_ptr;	/* Rx ring read pointer */
	unsigned int	cb_ptr;		/* Rx ring initial CB ptr */
	unsigned int	end_ptr;	/* Rx ring end CB ptr */
	unsigned int	old_discards;
	struct bcmgenet_net_dim dim;
	int		rx_max_coalesced_frames;
	int		rx_coalesce_usecs;
	void (*int_enable)(struct bcmgenet_rx_ring *);
	void (*int_disable)(struct bcmgenet_rx_ring *);
	struct bcmgenet_priv *priv;
};