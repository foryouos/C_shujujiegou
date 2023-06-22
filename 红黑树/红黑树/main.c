#include <stdio.h>
#include <stdlib.h>


//定义红和黑节点个数
#define RED 0
#define BLACK 1

//解决变量写死问题
typedef int KEY_TYPE;
//宏定义
#define RBTREE_ENTRY(name,type)      \
    struct name                      \
    {                                \
        /* data */                   \
        struct type *right;          \
        struct type *left;           \
        struct type *parent;         \
        unsigned char color;         \
    }
//红黑数节点定义
//单节点不可复用，
typedef struct _rbtree_node  //不可复用 _
{
    KEY_TYPE key;  //键
    void* value; //值
#if 1   //将以下指针成红黑树模版
    struct _rbtree_node* right;  //右节点
    struct _rbtree_node* left;  //左节点

    struct _rbtree_node* parent; //父节点
    unsigned char color;   //放最后面颜色，节省一点空间，字节对齐
#else
    RBTREE_ENTRY(, _rbtree_node) node;
#endif
}rbtree_node;

//一个结构体可以定义多个红黑树
/*
typedef struct thread  //不可复用 _
{
    KEY_TYPE key;  //键
    void* value; //值
#if 0   //将以下指针成红黑树模版
    struct _rbtree_node *right;  //右节点
    struct _rbtree_node *left;  //左节点

    struct _rbtree_node *parent; //父节点
    unsigned char color;   //放最后面颜色，节省一点空间，字节对齐
#else
    RBTREE_ENTRY( ,thread) ready;
    RBTREE_ENTRY( ,thread) wait;
    RBTREE_ENTRY( ,thread) sleep;
#endif
}rbtree_node;
*/


// 根节点指向头结点和叶子结点
typedef struct _rbtree
{
    struct _rbtree_node* root;   //头节点
    struct _rbtree_node* nil;   //叶子节点作为空间点,(所有叶子节点隐藏且都是隐藏的)nil好判断,避免内存不存在

}rbtree;



//左旋转  T红黑树 当前旋转的根节点  x 最上面的
void rbtree_left_rotate(rbtree* T, rbtree_node* x)
{
    rbtree_node* y = x->right; // y为目前阶段x的右节点
    // 1，先让x的右节点变为与的左节点
    x->right = y->left;
    if (y->left != T->nil)        // 如果y的左节点不为叶子节点 最顶部节点，是叶子节点就不用改了
    {
        y->left->parent = x;     //将y的左节点的父节点设置x
    }
    // 2,调整y的父节点
    y->parent = x->parent;
    //x 的父节点要么是根节点，要么是空     
    if (x->parent == T->nil) //若x的节点不为叶子节点
    {
        T->root = y;        //将T的根节点设为y
    }
    else if (x == x->parent->left) //若x为父节点的左节点
    {
        x->parent->left = y;   //将x的父节点的左节点设为y
    }
    else                         //若x为父节点的左节点
    {
        x->parent->right = y;   //将x的父节点的右节点设为y
    }
    // 3,调整y的左节点
    y->left = x;
    // 调整 x的父节点
    x->parent = y;
}
//右旋,y为旋转的节点最上面的
void rbtree_right_rotate(rbtree* T, rbtree_node* y)
{
    rbtree_node* x = y->left;
    //1,
    y->left = x->right;
    if (x->right != T->nil) //如果x的右节点不是叶子节点
    {
        x->right->parent = y;
    }
    // 2,
    x->parent = y->parent;
    if (y->parent == T->nil) //最顶部节点
    {
        T->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    //调整x和y的动向
    x->right = y;
    y->parent = x;
}

//插入节点z是红色，判断其父节点
//调整颜色 参数红黑树根节点，和节点z的颜色是红色
void rbtree_insert_fixup(rbtree* T, rbtree_node* z)
{
    //插入节点z是红色，判断其父节点是红色，违背了性质4
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left) //若z位于左节点
        {
            rbtree_node* y = z->parent->parent->right; //y为z的叔父节点
            if (y->color == RED) //如果叔父节点是红色
            {
                z->parent->color = BLACK;  //z的父节点换位黑色
                y->color = BLACK;          // z的叔父节点

                //设置祖父条件

                z->parent->parent->color = RED; //z的祖父节点为红色
                //z是红色，z的祖父已经完善啦，z回溯
                z = z->parent->parent;  //z在每次回溯的时候都是红色的

            }
            else //z的叔父节点是黑色的
            {
                if (z == z->parent->right) //当z位于右边部分时，要先转到左边进入中间状态
                {
                    //需要两次调整,
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                    
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                //右旋
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
        else  //当z为位于右边是
        {
            //获取其叔父节点
            rbtree_node* y = z->parent->parent->left; //y为z的叔父节点
            //判断其叔父节点是红色还是黑色
            if (y->color == RED)  //叔父的颜色是红色
            {
                z->parent->color = BLACK;  //z的父节点换位黑色
                y->color = BLACK;          // z的叔父节点
                z->parent->parent->color = RED; //z的祖父节点为红色
                //z是红色，z的祖父已经完善啦，z回溯
                //如果z的祖父为空
                z = z->parent->parent;  //z在每次回溯的时候都是红色的
               
            }
            else //其叔父的颜色是黑叔
            {
                if (z == z->parent->left) //当z位于右边部分时，要先转到左边进入中间状态
                {
                    //需要两次调整,
                    // //  z位置发生变化
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                    
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                //右旋
                    
                rbtree_left_rotate(T, z->parent->parent);
            }

        }
    }
    T->root->color = BLACK; //防止根节点的变红

}


// 插入
// 会插入到最低层
//插入的树 T，插入的节点 z
void rbtree_insert(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->root; //记录x之前的位置，即新节点的z的插入点
    rbtree_node* x = T->root; //指着头结点
    //开始循环，当x不等于叶子节点时，一直循环
    while (x != T->nil)
    {
        y = x; //y始终比x高一级;
        if (z->key < x->key)
        {
            //进入左子树
            x = x->left;
        }
        else if (z->key > x->key)
        {
            //进入右子树
            x = x->right;

        }
        else  //如果等于
        {
            //取决于业务
            return; //不做处理
        }
    } //得到了x是叶子结点
    z->parent = y;
    // 原来的树为空，新插入的节点作为根节点
    if (y == T->nil) //此时红黑树没有任何节点
    {
        T->root = z;
    }
    else if (z->key < y->key)  //插入到左节点
    {
        //将在插入到y的哪个位置
        y->left = z;

    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    //插入的颜色(上什么 颜色)
    z->color = RED; //一开始上色 红色 ，不改变性质黑数
    //颜色调整
     rbtree_insert_fixup(T, z);
}


//删除
//找到右子树中的最小节点
rbtree_node* rbtee_right_mini(rbtree* T, rbtree_node* x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}
//找到左左子树中的最大节点
rbtree_node* rbtee_left_max(rbtree* T, rbtree_node* x)
{
    while (x->right != T->nil)
    {
        x = x->right;
    }
    return x;
}
// 当删除节点有左右子树时
rbtree_node* rbtree_twice(rbtree* T, rbtree_node* z)
{
    rbtree_node* k = z->parent;
    // 后继节点就是中序遍历时右子树的第一个节点
    if (z->right != T->nil)
    {
        return rbtee_right_mini(T, z->right);
    }

    // 这里应该不会被执行到，因为此时的待删除节点必然有两个孩子节点
    // 如果没有右子树，那就是作为左子树时的根节点
    while ((k != T->nil) && (z == k->right))
    {
        z = k;
        k = k->parent;
    }
    return k;
}
//删除操作调整

void rbtree_delete_fixup(rbtree* T, rbtree_node* x)
{
    while ((x != T->root) && (x->color == BLACK)) //不是根节点且删除的节点为黑
    {
        //如果x位于父节点的左边
        if (x == x->parent->left)
        {
            //找到兄弟节点
            rbtree_node* w = x->parent->right;
            //情况1，兄弟节点为红色
            if (w->color == RED)
            {
                //1.1兄弟节点变成黑色
                w->color = BLACK;
                //1.2 父节点变成红色
                x->parent->color = RED;
                //1.3 父节点左旋
                rbtree_left_rotate(T, x->parent);
                //重新设置x的兄弟节点
                w = x->parent->right;
            }
            // 情况2
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                //兄弟节点变为红色
                w->color = RED;
                x = x->parent;
            }
            else
            {
                //情况3 x的兄弟节点是黑色的，兄弟的左孩子是红色，右孩子是黑色
                if ((w->right->color == BLACK))
                {
                    //3.1兄弟节点变红
                    w->color = RED;
                    //将左孩子变黑
                    w->left->color = BLACK;
                    // 已兄弟节点右旋
                    rbtree_right_rotate(T, w);
                    //重置x的兄弟节点
                    w = x->parent->right;
                }
                //情况4 x的兄弟节点是黑色，x的兄弟节点的右孩子是红色的
                //将兄弟节点换成父节点的颜色
                w->color = x->parent->color;
                //把付姐带你和兄弟节点的右孩子涂黑
                w->parent->color = BLACK;
                w->right->color = BLACK;
                //对父节点左旋
                rbtree_left_rotate(T, x->parent);
                // 设置x指针，指向根节点
                x = T->root;  //结束代码
            }
        }
        else //如果x位于x父节点的右边
        {
            rbtree_node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {

                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }
        }
    }
    // 继承节点变为黑色，为了弥补失去的黑高
    x->color = BLACK;
}
//根节点与要删除的子节点
rbtree_node* rbtree_delete(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->nil;// y指向要删除/移动替换的结点
    rbtree_node* x = T->nil;  //左右两个量的临时中转红黑树节点
    // 1,2如果z的左节点或者右节点为空
    if ((z->left == T->nil) || (z->right == T->nil))
    {
        y = z; //继续需要释放的节点

    }
    else //删除的节点有连个节点
    {
        // 儿子节点有两个孩子，用后继节点替换待删除的节点，问题转化为删除这个后继节点
        
        //根据z的位置去不同的值
        // z的有节点不为空，取右边最小的值，为删除的点
        y = rbtree_twice(T, z); 
        // 需要将 y与的值与z的值互换 接 3.2
    }
    // 如果儿子节点有独生子，那么这个独生子直接继承它爹的位置

    //若要释放的y仍有子节点，x取其子节点辅助
    if (y->left != T->nil)
    {
        x = y->left;
    }
    else if (y->right != T->nil)
    {
        x = y->right;
    }

    // 调节继位节点的parent指针指向
    x->parent = y->parent;  //隔离删除的节点y，若没有则为 root->nil
    // 调节父节点的孩子指针指向
    // 
    // y的父节点的子节点互换位置
    //根节点位置
    if (y->parent == T->nil)
    {
        // 根节点将被删除，更新根节点
        T->root = x;  //要删除的节点是根节点，将x顶上根节点
    }
    else if (y == y->parent->left)  //如果删除的节点位于左边
    {
        y->parent->left = x; 
    }
    else
    {
        y->parent->right = x;
    }

    // 3.2 如果y是右子树的最小节点，就将y放到z的位置，然后删除原来的z
    if (y != z)
    {
        z->key = y->key;
        z->value = y->value;
    }

    //如果删除的节点是黑色的，就要维护一下红黑树的性质
    if (y->color == BLACK) //破坏了黑高
    {
        //参数：红黑树根节点，当前要删除的结点
        rbtree_delete_fixup(T, x);
    }
    return y;
}

//查找节点
rbtree_node* rbtree_search(rbtree* T, KEY_TYPE key)
{
    rbtree_node* node = T->root;
    while (node != T->nil)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
        else
        {
            return node;  //返回查到的节点
        }
    }
    return T->nil; //没有找到
}

//中序遍历  node遍历开始的头结点
void rbtree_traversal_center(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        rbtree_traversal_center(T, node->left);
        printf("key:%d,color:%d\n", node->key, node->color);
        rbtree_traversal_center(T, node->right);
    }
}
//前序遍历  node遍历开始的头结点
void rbtree_traversal_front(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        printf("key:%d,color:%d\n", node->key, node->color);
        rbtree_traversal_front(T, node->left);
        rbtree_traversal_front(T, node->right);
    }
}
//前序遍历  node遍历开始的头结点
void rbtree_traversal_tail(rbtree* T, rbtree_node* node)
{
    if (node != T->nil)
    {
        rbtree_traversal_tail(T, node->left);
        rbtree_traversal_tail(T, node->right);
        printf("key:%d,color:%d\n", node->key, node->color);
    }
}

int main()
{
    int keyArray[20] = { 24,25,13,35,23, 26,67,47,38,98, 20,19,17,49,12, 21,9,18,14,15 };
    rbtree* T = (rbtree*)malloc(sizeof(rbtree));
    if (T == NULL)
    {
        printf("malloc failed");
        return -1;
    }
    T->nil = (rbtree_node*)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node* node = T->nil;
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        node = (rbtree_node*)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }
    //中序排序输出
    rbtree_traversal_center(T, T->root);
    printf("----------------------------------------\n");
    for (i = 0; i < 20; i++)
    {
        rbtree_node* node = rbtree_search(T, keyArray[i]);
        rbtree_node* cur = rbtree_delete(T, node);   
        free(cur);
        rbtree_traversal_center(T, T->root);
        printf("----------------------------------------\n");

    }

}