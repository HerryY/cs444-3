/******o*****************************************
 **Author: Jianzhi Li
 **Project: CS444 Project 2 SSTF I/O scheduler
 **Date: 10/19/15
 ***********************************************/


#include<linux/blkdev.h>
#include<linux/elevator.h>
#include<linux/bio.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/init.h>

struct sstf_data{

   struct list_head queue;


};

static void sstf_merged_requests(struct request_queue* q, struct request *rq, struct request *next){

	list_del_init(&next -> queuelist);

};

static int sstf_dispatch(struct request_queue *q, int force){

	struct sstf_data *nd = q -> elevator->elevator_data;
	printk("**********Start dispatch**********\n");
	printk("Dispatch  %llu -> \n", blk_rq_pos(rq));
	if(!list_empty(&nd->queue)){
	
	   struct request *rq;
	   rq = list_entry(nd -> next_to_dispatch, struct request, queuelist);
	   list_del_init(&rq -> queuelist);
  	   elv_dispatch_sort(q,rq);
	   return 1;	   
	}

	return 0;
}


static void sstf_add_request(struct request_queue *q, struct request *rq){

	struct sstf_data *nd = q -> elevator -> elevator_data;
	printk("Add %llu ->\n", blk_rq_pos(rq));

	if(list_empty(&nd -> queue)){
	
	//the first insert that is going to queue directly
		list_add_tail(&rq -> queuelist, &nd -> queue);
		printk("This is the first\n");
	
	
	}
	else{
	
	struct list_head *pos;
	int flag = 0;

	sector_t index_req_sector = q -> end_sector;//the current location of sector
	sector_t insert_req_sector = blk_rq_pos(rq);//the new request for a sector

	unsigned long long curr, next;
	//the curr is the distance of the sector to a request sector
	//the next is the distance of current sector going to the next request sector
	
	list_for_each(pos, &nd -> queue){
	
		struct request *curr_req;
		curr_req = list_entry(pos, struct request, queuelist);
		sector_t curr_req_sector = blk_rq_pos(curr_req);

		if(insert_seq_sector >= index_req_sector)
		   curr = insert_seq_sector - index_req_sector;
		else
		   curr = index_req_sector - insert_seq_sector;
		if(curr_req_sector >= index_req_sector)
		  next = curr_req_sector - insert_req_sector;
		else
		   next = insert_req_sector - curr_req_sector;
		//sort the result, if the curr is more nearly than the next then we choose the nearest one
		if(curr <= next){
		
			list_add_tail(&rq -> queuelist, pos);
			printk("This is the last sector = %llu\n", curr_req_sector);
			flag = 1;
			break;
	  }
	
		//future comparision that is depends on the result from the last comparision.		
		index_req_sector = curr_req_sector;
	
     }
	
	if(flag == 0){ //if there has a sector never been insert in the queue that is mean
	   //that sector is the farest one so that is never been inserted.
				
	   list_add_tail(&rq -> queuelist, pos);
	   printk("This is the head of head(last of sector)\n");
	
	
	}
   }
}


static struct request *sstf_former_request(struct request_queue *q, struct request *rq){

   struct sstf_data *nd = q -> elevator -> elevator_data;

   if(rq -> queuelist.prev == &nd -> queue)
      return NULL;
   return list_entry(rq -> queuelist.prev, struct request, queuelist);

}


static struct request *sstf_latter_request(struct request_queue *q, struct request *rq){

	struct sstf_data *nd = q -> elevator -> elecator_data;

	if(rq -> queuelist.nect == &nd -> queue)
	   return NULL;
	return list_entry(rq -> queuelist.next, struct request, queuelist);

}

static void *sstf_init_queue(struct request_queue *q){

	struct sstf_data *nd;
	nd = kmalloc_node(sizeof(*nd), GFP_KERNEL, q -> node);
	if(!nd)
	   return NULL;
	INIT_LIST_HEAD(&nd -> queue);

	nd -> dir = 1;
	nd -> pos = 0;
	return nd;


}


static void sstf_exit_queue(struct elevator_queue *e){

	struct sstf_data*nd = e -> elevator_data;
	BUG_ON(!list_empty(&nd -> queue));
	kfree(nd);
}

static struct elevator_type elevator_noop = {
	.ops = {
	
	
		.elevator_merge_req_fn		= noop_merged_requests,
		.elevator_dispatch_fn		= noop_dispatch,
		.elevator_add_req_fn		= noop_add_request,
		.elevator_former_req_fn		= noop_former_request,
		.elevator_latter_req_fn		= noop_latter_request,
		.elevator_init_fn		= noop_init_queue,
		.elevator_exit_fn		= noop_exit_queue,
	
	
	},
	.elevator_name = "sstf",
	.elevator_owner = THIS_MODULE,


};

static int __init sstf_init(void){

   return elv_register(&elevator_sstf);

}

static void __exit sstf_exit(void){

	elv_unregister(&elevator_sstf);

}

module_init(sstf_init);
module_exit(sstf_exit);

MODULE_AUTHOR("Jianzhi Li")
MODULE_LICENSE("GPL")
MODULE_DESCRIPTION("SSTF IO SCHEDULER")
