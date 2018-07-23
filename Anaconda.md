# Anaconda

> Anaconda就是一个对python的包管理和版本管理工具。

一般还是习惯先创建环境，在环境里怎么瞎胡乱整都不会影响全局，大不了玩坏了把这个环境删了重新再建一个。

## 创建环境

```
conda create -n env1 python=3.6
```

创建一个名为env1的环境，该环境的版本为python3.6，名字和python版本根据需要修改。

## 列出当前所有环境

```
conda info --envs
```

现在应该有个环境叫pytorch。

## 进入环境

```
activate env1
```

进入名为env1的环境。

## 执行python代码

打开txt，写个

```python
print(1+2)
```

保存并将该文件的后缀改为.py（test.py）。

进入环境，并切换到文件所在目录，执行

```
python test.py 
```

就能看到输出3。

或者下个IDE，直接点运行就能看结果，先开个坑pycharm的配置后面再补。

## 退出环境

```
deactivate
```

## 删除环境

```
conda remove -n env1 --all
```

删除名为env1的环境。

