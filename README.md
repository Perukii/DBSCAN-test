# DBSCAN-test
DBSCANのテスト。索引にはRtreeを使用

### 依存パッケージ

 - [Gtkmm](https://github.com/GNOME/gtkmm) 別途環境構築が必要。
 - [RTree](https://github.com/nushoin/RTree) インストール不要。

### ビルド例

```
g++ -o dbscan dbscan.cpp `pkg-config --libs --cflags gtkmm-3.0`
```

