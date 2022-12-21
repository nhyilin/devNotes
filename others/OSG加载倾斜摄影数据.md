通过生成一个索引文件，使用OpenSceneGraph加载倾斜摄影数据。

## 1. 概述
ContextCapture（Smart3D）生成的倾斜摄影模型数据一般都形如如下组织结构：
```tree
- Data
    - Tile_+000
    - Tile_+001
    ...
- metadata.xml
```

在Data目录下包含了分块的瓦片数据，每个瓦片都是一个LOD文件夹。osg能够直接读取osgb格式，理论上只需要依次加载每个LOD的金字塔层级最高的osgb，整个倾斜摄影模型数据就加载进来了。不过有点麻烦的是这类数据缺乏一个整体加载的入口，如果每次加载都遍历整个文件夹加载的话，会影响加载的效率。所以一般的数据查看软件都会为其增加一个索引。

这里就给倾斜摄影数据添加一个osgb格式的索引文件，生成后就可以通过OSG直接加载整个倾斜摄影模型数据。

## 2. 实例
### 2.1. 代码
具体的实现代码如下：
```cpp
#include <iostream>
#include <string>

#include <QDir>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

using namespace std;

//查找目录下所有的文件夹
static void findDir(string dir, vector<string>& subDirs)
{
	//
	subDirs.clear();
	QDir fromDir(QString::fromLocal8Bit(dir.c_str()));
	QStringList filters;

	//
	QFileInfoList fileInfoList = fromDir.entryInfoList(filters, QDir::AllDirs | QDir::Files);
	foreach(QFileInfo fileInfo, fileInfoList)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
		{
			continue;
		}

		if (fileInfo.isDir())
		{
			QByteArray dir = fileInfo.filePath().toLocal8Bit();
			subDirs.push_back(dir.data());
		}
	}
}

//得到文件路径的文件名   C:\\b\\a(.txt) -> a
static std::string DirOrPathGetName(std::string filePath)
{
	size_t m = filePath.find_last_of('/');
	if (m == string::npos)
	{
		return filePath;
	}

	size_t p = filePath.find_last_of('.');
	if (p != string::npos && p > m)				//没有点号或者
	{
		filePath.erase(p);
	}

	std::string dirPath = filePath;
	dirPath.erase(0, m + 1);
	return dirPath;
}

void createObliqueIndexes(std::string fileDir)
{
	string dataDir = fileDir + "/Data";

	osg::ref_ptr<osg::Group> group = new osg::Group();
	vector<string> subDirs;
	findDir(dataDir, subDirs);

	for (size_t i = 0; i < subDirs.size(); i++)
	{
		string name = DirOrPathGetName(subDirs[i]);
		string path = subDirs[i] + "/" + name + ".osgb";

		osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(path);
		osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD();

		auto bs = node->getBound();
		auto c = bs.center();
		auto r = bs.radius();
		lod->setCenter(c);
		lod->setRadius(r);
		lod->setRangeMode(osg::LOD::RangeMode::PIXEL_SIZE_ON_SCREEN);
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->getOrCreateStateSet();
		lod->addChild(geode.get());

		std::string relativeFilePath = "./Data/" + name + "/" + name + ".osgb";  //相对路径

		lod->setFileName(0, "");
		lod->setFileName(1, relativeFilePath);

		lod->setRange(0, 0, 1.0);																							//第一层不可见
		lod->setRange(1, 1.0, FLT_MAX);

		lod->setDatabasePath("");

		group->addChild(lod);
	}
	std::string outputLodFile = fileDir + "/Data.osgb";
	osgDB::writeNodeFile(*group, outputLodFile);
}

int main(int argc, char *argv[])
{
	string fileDir = "D:/Data/scene/city";
	std::string outputLodFile = fileDir + "/Data.osgb";
	createObliqueIndexes(fileDir);

	osgViewer::Viewer viewer;
	osg::Node * node = new osg::Node;
	node = osgDB::readNodeFile(outputLodFile);
	viewer.setSceneData(node);

	return viewer.run();
}
```

### 2.2. 解析
如果直接读取每一块的LOD然后通过osgDB::writeNodeFile写入到一个osgb文件，这个文件就会保存所有块的LOD第一层信息。这样在第二册加载的时候还是会比较慢，所以这里就创建了一个空的节点，形成了索引所有LOD块的数据结构。对于每一块数据，新建两层LOD，第一层为自身的空白节点，第二层为分块LOD的第一层数据：
```cpp
osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(path);
osg::ref_ptr<osg::PagedLOD> lod = new osg::PagedLOD();

auto bs = node->getBound();
auto c = bs.center();
auto r = bs.radius();
lod->setCenter(c);
lod->setRadius(r);
lod->setRangeMode(osg::LOD::RangeMode::PIXEL_SIZE_ON_SCREEN);
osg::ref_ptr<osg::Geode> geode = new osg::Geode;
geode->getOrCreateStateSet();
lod->addChild(geode.get());

std::string relativeFilePath = "./Data/" + name + "/" + name + ".osgb";  //相对路径

lod->setFileName(0, "");
lod->setFileName(1, relativeFilePath);

lod->setRange(0, 0, 1.0);																							//第一层不可见
lod->setRange(1, 1.0, FLT_MAX);

lod->setDatabasePath("");

group->addChild(lod);
```
LOD的Center和Radius都非常重要，需要预先设置好；setRangeMode设置了细节层级调度的模式，一般都为PIXEL_SIZE_ON_SCREEN；setFileName设置了每一层的数据路径，setRange确定了当前层级的范围。由于这个LOD只是个索引文件，所以会设置第二层为极大的可见范围值。

## 3. 结果
可以像加载普通OSGB文件一样加载这个索引文件。