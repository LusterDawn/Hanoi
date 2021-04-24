# -
汉诺塔与栈的关系，一次小小的尝试
一、代码层解释：
  1.第一步是创建三个栈：A、B、C，并全栈赋值为0
  2.第二步是定义栈顶指针（指向各个data[1]）、栈底指针(指向各个data[0])
图片：![image](https://user-images.githubusercontent.com/83108067/115949499-2b514580-a508-11eb-8560-66b8f4a2c64f.png)
  3.第三步：接受用户输入汉诺塔的层数，依次push入栈（以4层塔为例）
  4.第四步：利用下一页的自研规律移动木块，每次递归都会生成一座塔（其高度从2到用户输入的汉诺塔阶数），直到最终在C柱达成最后目标
图片![image](https://user-images.githubusercontent.com/83108067/115949529-5fc50180-a508-11eb-9b89-02fe589f2c45.png)

二、算法层解释
  图片：
  ![image](https://user-images.githubusercontent.com/83108067/115949562-8edb7300-a508-11eb-918c-aafeec438505.png)
  
 如果大家有什么简化的方法？欢迎创建一个new branch（源文件的备份），并在备份上进行修改/新增功能，修改完成后点击pull request，进入讨论环节，如果新代码没有出现错误，就可以merge（融合新增代码）/直接使用新代码
