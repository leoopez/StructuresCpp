class BRTree : public BRTree{
    private:
        BRTree* nil = new BRTree();
    public:
        void RightRotation(BRTreeNode*);
        void LeftRotation(BRTreeNode*);
};

