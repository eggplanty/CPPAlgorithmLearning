//
// Created by sen on 2020/6/1.
//

/**
 * BFS 最短路
 *
 * define queue = { first point } // 每层待处理列表
 * define cnt = 0 // 计算路径长度
 * define queue memory = {} // 防止走重复路，这可以直接在原始数据上修改
 *
 * while (!queue.empty()) {
 *      size = queue.size()
 *      cnt++ // 按层计算路径长度
 *      while (size-- > 0) { // 遍历每层节点
 *          tmp = queue.get()
 *          if (tmp in memory) // 不走重复路
 *              continue
 *
 *          if (finish()) // 满足退出条件
 *              return
 *
 *          memory[tmp] = 1 // 标记
 *
 *          process...{
 *              queue.add() // 将满足条件的点加入到下层待搜索列表中
 *          }
 *      }
 * }
 */


/**
 * DFS 连通性
 *
 * 返回数据 dfs(原始数据data，已处理记录visited或者开始结束标识st ed（有时就在原始数据上记录），当前要处理数据的id，其他) {
 *      if (满足终止条件：主要是超出边界或者已经处理过)
 *          return ;
 *
 *      process data ... // 处理数据
 *
 *      visited[k] = 1; // 标识已处理
 *
 *      next_process ... {
 *          ret = dfs(...) // 处理下层递归，同时可能需要处理返回值
 *      }
 *
 *      return ;
 * }
 */


/**
 * Back Tracking 得到所有组合的可能性
 *
 * define ans;
 * backtracking(一个结果prefix，原始数据data，已处理记录visited或者开始结束标识st ed（有时就在原始数据上记录），当前要处理数据的id，其他) {
 *      if (满足终止条件：主要是超出边界或者已经处理过) {
 *          add_ans(prefix); // 副本加入结果集，prefix常见有两种，一种是需要具体结果，另一种不需要具体结果，那么可以使用int等来做简化统计
 *          return ;
 *      }
 *
 *
 *      process data ... // 处理数据
 *
 *      visited[k] = 1; // 标识已处理, 处理和回退有时候和下层递归处理是紧耦合的
 *
 *      next_process ... {
 *
 *          add_prefix  //对prefix和对visited一样处理，如果是int可以简化
 *          ret = dfs(...) // 处理下层递归，同时可能需要处理返回值
 *          delete_prefix
 *      }
 *
 *      visited[k] = 0; // 当前递归链结束后标识为未处理
 * }
 *
 */

/**
 * backtracking 计数框架
 * 不获取所有结果的具体内容，只计算结果长度是否和目标一致
 */