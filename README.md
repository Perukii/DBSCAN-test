# DBSCAN-test
DBSCANのテスト。索引にはRtreeを使用



### 依存パッケージ

 - [Gtkmm](https://github.com/GNOME/gtkmm) 別途環境構築が必要。
 - [RTree](https://github.com/nushoin/RTree) インストール不要。

### ビルド例

```
g++ -o dbscan dbscan.cpp `pkg-config --libs --cflags gtkmm-3.0`
```
### スクリーンショット
![Screenshot from 2020-10-07 20-43-25](https://user-images.githubusercontent.com/57752033/100536973-ba16aa80-3267-11eb-84cd-f57f9c0265af.png)
![Screenshot from 2020-10-07 20-42-46](https://user-images.githubusercontent.com/57752033/100536974-bb47d780-3267-11eb-839f-32fccc1c929d.png)
