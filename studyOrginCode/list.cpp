typedef struct xLIST
{
	listFIRST_LIST_INTEGRITY_CHECK_VALUE				
	volatile UBaseType_t uxNumberOfItems;       //包含列表项个数
	ListItem_t * pxIndex;			            //当前列表项索引号，用于遍历列表（listGET_OWNER_OF_NEXT_ENTRY）
	MiniListItem_t xListEnd;					//列表中最后一个列表项
	listSECOND_LIST_INTEGRITY_CHECK_VALUE				
} List_t;

struct xMINI_LIST_ITEM
{
    listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE 
    configLIST_VOLATILE TickType_t xItemValue;              //列表列表项值
    struct xLIST_ITEM * configLIST_VOLATILE pxNext;         //下一个列表项
    struct xLIST_ITEM * configLIST_VOLATILE pxPrevious;     //前一个列表项
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

typedef struct xLIST_ITEM
{
	listFIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE			
	configLIST_VOLATILE TickType_t xItemValue;			//列表项值
	struct xLIST_ITEM * configLIST_VOLATILE pxNext;		//下一个列表项
	struct xLIST_ITEM * configLIST_VOLATILE pxPrevious;	//前一个列表项
	void * pvOwner;										//链表项归谁拥有
	struct xLIST * configLIST_VOLATILE pxContainer;		//此列表项归哪个列表
	listSECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE			
};
typedef struct xLIST_ITEM ListItem_t;

//列表初始化
void vListInitialise( List_t * const pxList )
{
    pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd ); //索引项指向列表最后一项
    //初始化列表最后一项shuoying
    pxList->xListEnd.xItemValue = portMAX_DELAY;    //列表项值设为最大
    pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );       //前一项后一项都指向自己
    pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd ); 
    pxList->uxNumberOfItems = ( UBaseType_t ) 0U;                           //列表数量为0
    listSET_LIST_INTEGRITY_CHECK_1_VALUE( pxList );  
    listSET_LIST_INTEGRITY_CHECK_2_VALUE( pxList );  
}

//列表项初始化
void vListInitialiseItem( ListItem_t * const pxItem )
{
	pxItem->pxContainer = NULL; //此列表项归的列表为空
    listSET_FIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem );
    listSET_SECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem );
}

//列表中插入列表项
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t *pxIterator;
    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

    //对列表和列表项的完整性检查
    listTEST_LIST_INTEGRITY( pxList );
    listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

    //插入到最后
    if( xValueOfInsertion == portMAX_DELAY )
    {
        //放多倒数第二个位置
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        //  ITEM2（50） ITEM3（45） ITEM1（40） END
        for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); 
                pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
                pxIterator = pxIterator->pxNext ) 
        {
        }
    }

    //插入项的下一个 = 当前项的下一个
    pxNewListItem->pxNext = pxIterator->pxNext;
    //插入项下一个的下一个 = 插入项
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;
    //插入项下一个的上一个 = 当前项
    pxNewListItem->pxPrevious = pxIterator;
    //当前项的下一个 = 插入项
    pxIterator->pxNext = pxNewListItem;

    //设定列表项归哪个列表
    pxNewListItem->pxContainer = pxList;
    //+1
    ( pxList->uxNumberOfItems )++;
}

//列表项插入到列表尾
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t * const pxIndex = pxList->pxIndex;
    
	listTEST_LIST_INTEGRITY( pxList );
	listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

    //插入项的上一项和下一项 赋值
	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;

	//无用
	mtCOVERAGE_TEST_DELAY();

    //插入项的下一项和上一项指向插入项
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	pxIndex->pxPrevious = pxNewListItem;

	//此列表项归的列表
	pxNewListItem->pxContainer = pxList;

    //列表包含项数量+1
	( pxList->uxNumberOfItems )++;
}

//列表项的删除
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
    //此列表项归的列表
    List_t * const pxList = pxItemToRemove->pxContainer;

    //列表项上一项 和下一项互链
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    mtCOVERAGE_TEST_DELAY();

    //删除的是索引项
    if( pxList->pxIndex == pxItemToRemove )
    {
        //指向索引项的上一项
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    //此列表项归的列表为空
    pxItemToRemove->pxContainer = NULL;
    
    //列表包含项数量+1
    ( pxList->uxNumberOfItems )--;

    //返回列表包含项数量
    return pxList->uxNumberOfItems;
}

//获取列表的下一个列表的所有者
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )										
{			
    /*当前列表*/																		     
    List_t * const pxConstList = ( pxList );												
	/*pxIndex 变量指向下一个列表项*/  
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;																			\
	/*下一个列表项是列表尾 指向下一个列表项（列表头）*/
	if( ( void * ) ( pxConstList )->pxIndex == ( void * ) &( ( pxConstList )->xListEnd ) )	
	{																						
		( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;						
	}																						
    /*返回列表的所有者*/
	( pxTCB ) = ( pxConstList )->pxIndex->pvOwner;											
}