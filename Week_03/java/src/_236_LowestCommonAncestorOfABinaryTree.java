/**
 * 第一遍：2020/06/08周一 ✅
 * 第二遍：2020/09/12周六 ✅
 * 第三遍：2020/09/12周日 ✅
 * 第四遍：2020/06/29周一
 * 因为要求二叉树的最近公共祖先，所以就要考虑是最近公共祖先的节点应该满足什么条件。
 * 思路应该这么来。
 */
class _236_LowestCommonAncestorOfABinaryTree {
    private TreeNode ancestor;

    /**
     * 时间O(n)
     * 空间O(logn) 最差O(n)
     */
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        dfs(root, p, q);
        return ancestor;
    }

    /**
     * 如果node是p和q的最低公共祖先，
     * 则node的左子树包含p或q并且node的右子树包含p或者q，
     * 或者 node是p或q并且node的左子树或右子树包含p或q
     *
     * @return true表示node这棵树包含p或q
     */
    private boolean dfs(TreeNode node, TreeNode p, TreeNode q) {
        if (node == null) return false;
        boolean l = dfs(node.left, p, q);
        boolean r = dfs(node.right, p, q);
        if ((l && r) || ((r || l) && (node.val == q.val || node.val == p.val))) {
            ancestor = node;
        }
        return node.val == q.val || node.val == p.val || l || r;
    }

    class ReturnNode {
        /**
         * 返回值为null则表示root这棵树不包含p和q
         * 返回值不为null则有两种情况，
         * 1.如果root这棵树只包含p或者q，则返回p或者q
         * 2.如果root这棵树同时包含p或者q，则返回p或者q的最低公共祖先
         * 因此这个解法的返回值存在二义性，这一点并不好。
         */
        public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
            if (root == null || root == p || root == q) return root;
            TreeNode l = lowestCommonAncestor(root.left, p, q);
            TreeNode r = lowestCommonAncestor(root.right, p, q);
            if (l != null && r != null) return root;
            return l != null ? l : r;
        }
    }

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }
}