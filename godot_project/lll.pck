GDPC                                                                             (   @   res://.import/Attack-0.png-7482f60561fc200689c4a1bf566fdfb1.stex�	     ,      �ߋ��kؘ}��D   res://.import/UI_tileset.png-9f1d9b8d9fab44b31a2cb0c6f9ce69bd.stex   �      �      ��C�j��;	��l��mD   res://.import/Vorota-0004.png-c54c1166b5c14ae154cfeb672997e89e.stex (      �       ว����Nb�W�S�<   res://.import/icon.png-1ada42475fe106c59fb9885a73678c1a.stex`�      U      -��`�0��x�5�[@   res://.import/icon11.png-f267e31b93f4c729cbda1d5f295e0680.stex  ��      U      -��`�0��x�5�[H   res://.import/level1_tileset.png-88b33549c071958c3175ffba487404d2.stex  �     !      ?�Ԉ gY$Ѵq�Y�{�H   res://.import/level1_tileset.png-da6487615126c3e3b7471dc277f2a761.stex  ��      �       ว����Nb�W�S�H   res://.import/level1_tileset.png-ebaf426714cf87313ead9c65229c7304.stex  �A      �'      ��G[����,p�����<   res://.import/lvl.png-04da9d90d36d937886ccb1aeb366b1ef.stex �l      G	      H�xÅC���zQ_��<   res://.import/lvl.png-0dcc3b71a274691c79d2d8a230667a74.stex �L     G	      H�xÅC���zQ_��<   res://.import/lvl.png-3b89ab86d69819db1ac9132df0c57077.stex `�      G	      H�xÅC���zQ_��@   res://.import/skull.png-9bdf1057fc7aa45578db5c3824c62be8.stex   `     �      t��~�U����w4vY@   res://.import/unnamed.png-bb1b93ae4e138561c1b371b914ec6d3f.stex @j     �K      <���Yſ�Y@� |��(   res://Assets/Prefabs/SpikeTileMap.gdns         �       ���t�Oz�;�f��$   res://Assets/Prefabs/TileMaps.tscn         �      �i��Gj�9��D(   res://Assets/Prefabs/bullet_prefab.tscn  $            ����BfJ��!X7�<   res://Assets/Sprites/Tilesets/Level1/Vorota-0004.png.import  ?      �      *,��vI\K!IR��@   res://Assets/Sprites/Tilesets/Level1/level1_tileset.png.import  �i      �      ���%!sS0�˄;��4   res://Assets/Sprites/Tilesets/Level1/lvl.png.import �u      �      ^Ƃ�yȥ��=H����0   res://Assets/Sprites/Tilesets/UI_tileset.tres   �x      �      �=�e�b� �|=��܂;4   res://Assets/Sprites/Tilesets/level1_tileset.tres   0�      �*      �ܬ�1��s���U/0   res://Assets/Sprites/UI/UI_tileset.png.import   ��      �      �cvB)j@��d�͏���$   res://Assets/Sprites/icon.png.import��      �      ��C�;��a{��~�Kqh(   res://Assets/Sprites/icon11.png.import  ��      �      _���m�Yӗ_�1kv�0   res://Assets/Sprites/level1_tileset.png.import  ��      �      �s�TjJ$͏,2��$   res://Assets/Sprites/lvl.png.import �      �      ��&g0������`���>(   res://Assets/Sprites/skull.png.import         �      �C�i�11"�a'Ngr�   res://Attack-0.png.import        �      ݈��^��B|G�m._�   res://CameraController.gdns �     �       ��mS���_�_���$�   res://Scripts/Enemy.gdns�     �       >M�c��ך�(�1$   res://Scripts/PlayerController.gdns p     �       �����r����0\�   res://Scripts/bullet.gdns   `     �       �#2Ξ�/΄5�l
�   res://default_env.tres  @     �       um�`�N��<*ỳ�8    res://level1_tileset.png.import 4     �      �wq��L������S�   res://level1_tileset.tres   �6     �      N����T��ҟ��   res://lvl.png.import V     }      zѵ�k��3� Mm���^   res://main_scene.tscn   �X     �      �"�
��
�_�l|�n   res://project.binaryp�     B%      ��*�Z�?�j>��   res://scripts.gdnlib�i     �       ۠��֋ҪY8�   res://unnamed.png.import�     �      :�釕mޖRA��jL        [gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "Spike"
class_name = "Spike"
library = ExtResource( 1 )
            [gd_scene load_steps=5 format=2]

[ext_resource path="res://Assets/Sprites/Tilesets/level1_tileset.tres" type="TileSet" id=1]
[ext_resource path="res://Assets/Sprites/Tilesets/UI_tileset.tres" type="TileSet" id=2]
[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=3]

[sub_resource type="NativeScript" id=1]
resource_name = "Spike"
class_name = "Spike"
library = ExtResource( 3 )

[node name="TileMaps" type="Node"]

[node name="GroundTileMap" type="TileMap" parent="."]
tile_set = ExtResource( 1 )
cell_size = Vector2( 32, 32 )
format = 1
tile_data = PoolIntArray( -131081, 0, 0, -131080, 0, 0, -131079, 0, 0, -131078, 0, 0, -131077, 0, 0, -131076, 0, 0, -131075, 0, 0, -131074, 0, 0, -131073, 0, 0, -196608, 0, 0, -196607, 0, 0, -196606, 0, 0, -196605, 0, 0, -196604, 0, 0, -196603, 1, 0, -196602, 0, 0, -196601, 0, 0, -65545, 0, 0, -65544, 0, 0, -65543, 1, 0, -65542, 0, 0, -65541, 0, 0, -65540, 0, 0, -65539, 0, 0, -65538, 0, 0, -65537, 0, 0, -131072, 0, 0, -131071, 0, 0, -131070, 0, 0, -131069, 0, 0, -131068, 0, 0, -131067, 0, 0, -131066, 0, 0, -131065, 0, 0, -9, 0, 0, -8, 0, 0, -7, 1, 0, -6, 1, 0, -5, 0, 0, -4, 0, 0, -3, 0, 0, -2, 0, 0, -1, 0, 0, -65536, 0, 0, -65535, 0, 0, -65534, 0, 0, -65533, 0, 0, -65532, 0, 0, -65531, 0, 0, -65530, 0, 0, -65529, 0, 0, 65527, 0, 0, 65528, 0, 0, 65529, 0, 0, 65530, 0, 0, 65531, 0, 0, 65532, 0, 0, 65533, 0, 0, 65534, 0, 0, 65535, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0, 0, 4, 0, 0, 5, 0, 0, 6, 0, 0, 7, 0, 0, 131063, 0, 0, 131064, 0, 0, 131065, 0, 0, 131066, 0, 0, 131067, 0, 0, 131068, 0, 0, 131069, 0, 0, 131070, 0, 0, 131071, 0, 0, 65536, 0, 0, 65537, 0, 0, 65538, 0, 0, 65539, 0, 0, 65540, 0, 0, 65541, 0, 0, 65542, 0, 0, 65543, 0, 0, 196599, 0, 0, 196600, 0, 0, 196601, 0, 0, 196602, 0, 0, 196603, 0, 0, 196604, 0, 0, 196605, 0, 0, 196606, 0, 0, 196607, 0, 0, 131072, 0, 0, 131073, 0, 0, 131074, 0, 0, 131075, 0, 0, 131076, 0, 0, 131077, 0, 0, 131078, 0, 0, 131079, 0, 0, 262135, 0, 0, 262136, 0, 0, 262137, 0, 0, 262138, 0, 0, 262139, 0, 0, 262140, 0, 0, 262141, 0, 0, 262142, 0, 0, 262143, 0, 0, 196608, 0, 0, 196609, 0, 0, 196610, 0, 0, 196611, 0, 0, 196612, 0, 0, 196613, 0, 0, 196614, 0, 0, 196615, 0, 0, 327671, 0, 0, 327672, 0, 0, 327673, 0, 0, 327674, 0, 0, 327675, 0, 0, 327676, 0, 0, 327677, 0, 0, 327678, 0, 0, 327679, 0, 0, 262144, 0, 0, 262145, 0, 0, 262146, 0, 0, 262147, 1, 0, 262148, 1, 0, 262149, 0, 0, 262150, 0, 0, 262151, 0, 0, 393207, 0, 0, 393208, 0, 0, 393209, 0, 0, 393210, 0, 0, 393211, 0, 0, 393212, 0, 0, 393213, 0, 0, 393214, 0, 0, 393215, 0, 0, 327680, 0, 0, 327681, 0, 0, 327682, 0, 0, 327683, 0, 0, 327684, 0, 0, 327685, 0, 0, 327686, 0, 0, 327687, 0, 0 )

[node name="WallTileMap" type="TileMap" parent="."]
tile_set = ExtResource( 1 )
cell_size = Vector2( 32, 32 )
collision_layer = 3
format = 1
tile_data = PoolIntArray( -327690, 9, 0, -327689, 9, 0, -327688, 9, 0, -327687, 9, 0, -327686, 9, 0, -327685, 9, 0, -327684, 9, 0, -327683, 9, 0, -327682, 9, 0, -327681, 9, 0, -393216, 9, 0, -393215, 9, 0, -393214, 9, 0, -393213, 9, 0, -393212, 9, 0, -393211, 9, 0, -393210, 9, 0, -393209, 9, 0, -393208, 9, 0, -262154, 9, 0, -262153, 14, 0, -262152, 14, 0, -262151, 14, 0, -262150, 14, 0, -262149, 14, 0, -262148, 14, 0, -262147, 14, 0, -262146, 14, 0, -262145, 14, 0, -327680, 14, 0, -327679, 14, 0, -327678, 14, 0, -327677, 14, 0, -327676, 14, 0, -327675, 14, 0, -327674, 14, 0, -327673, 14, 0, -327672, 9, 0, -196618, 9, 0, -196617, 14, 0, -196616, 14, 0, -196615, 14, 0, -196614, 14, 0, -196613, 14, 0, -196612, 14, 0, -196611, 14, 0, -196610, 14, 0, -196609, 14, 0, -262144, 14, 0, -262143, 14, 0, -262142, 14, 0, -262141, 14, 0, -262140, 14, 0, -262139, 14, 0, -262138, 14, 0, -262137, 14, 0, -262136, 9, 0, -131082, 9, 0, -196600, 9, 0, -65546, 9, 0, -131064, 9, 0, -10, 9, 0, -65528, 9, 0, 65526, 9, 0, 8, 9, 0, 131062, 9, 0, 65544, 9, 0, 196598, 9, 0, 131080, 9, 0, 262134, 9, 0, 196616, 9, 0, 327670, 9, 0, 262152, 9, 0, 393206, 9, 0, 327688, 9, 0, 458742, 9, 0, 458743, 9, 0, 458744, 9, 0, 458745, 9, 0, 458746, 9, 0, 458747, 9, 0, 458748, 9, 0, 458749, 9, 0, 458750, 9, 0, 458751, 9, 0, 393216, 9, 0, 393217, 9, 0, 393218, 9, 0, 393219, 9, 0, 393220, 9, 0, 393221, 9, 0, 393222, 9, 0, 393223, 9, 0, 393224, 9, 0 )

[node name="SpikeTileMap" type="TileMap" parent="." groups=[
"spike",
]]
tile_set = ExtResource( 1 )
cell_size = Vector2( 32, 32 )
format = 1
tile_data = PoolIntArray( -65541, 16, 0, 131072, 19, 0, 131073, 19, 0, 327672, 17, 0, 327673, 17, 0 )
script = SubResource( 1 )

[node name="UiTileMap" type="TileMap" parent="."]
tile_set = ExtResource( 2 )
cell_size = Vector2( 32, 32 )
format = 1
tile_data = PoolIntArray( -131073, 2, 0, -2, 8, 0, 65527, 5, 0, 7, 5, 0, 393215, 2, 0 )

[node name="DoorTileMap" type="TileMap" parent="."]
tile_set = ExtResource( 1 )
cell_size = Vector2( 32, 32 )
format = 1
tile_data = PoolIntArray( -262145, 23, 0, -9, 24, 0, -65529, 25, 0, 65535, 20, 0, 393215, 26, 0 )

[node name="ShadowTileMap" type="TileMap" parent="."]
tile_set = ExtResource( 1 )
cell_size = Vector2( 32, 32 )
format = 1
tile_data = PoolIntArray( -262153, 21, 0, -262152, 21, 0, -262151, 21, 0, -262150, 21, 0, -262149, 21, 0, -262148, 21, 0, -262147, 21, 0, -262146, 21, 0, -262145, 21, 0, -327680, 21, 0, -327679, 21, 0, -327678, 21, 0, -327677, 21, 0, -327676, 21, 0, -327675, 21, 0, -327674, 21, 0, -327673, 21, 0, -131081, 22, 0, -131080, 22, 0, -131079, 22, 0, -131078, 22, 0, -131077, 22, 0, -131076, 22, 0, -131075, 22, 0, -131074, 22, 0, -131073, 22, 0, -196608, 22, 0, -196607, 22, 0, -196606, 22, 0, -196605, 22, 0, -196604, 22, 0, -196603, 22, 0, -196602, 22, 0, -196601, 22, 0 )
          [gd_scene load_steps=5 format=2]

[ext_resource path="res://Scripts/bullet.gdns" type="Script" id=1]
[ext_resource path="res://Assets/Sprites/icon.png" type="Texture" id=2]

[sub_resource type="CircleShape2D" id=1]
radius = 3.23369

[sub_resource type="CircleShape2D" id=2]
radius = 1.23328

[node name="bullet" type="KinematicBody2D"]
scale = Vector2( 5, 5 )
collision_layer = 0
collision_mask = 0
script = ExtResource( 1 )
direction = Vector2( 8, 8 )
speed = 500.0

[node name="CollisionShape2D" type="CollisionShape2D" parent="."]
shape = SubResource( 1 )
disabled = true

[node name="Sprite" type="Sprite" parent="CollisionShape2D"]
position = Vector2( -0.0834332, 0.0834293 )
scale = Vector2( 0.105761, 0.105762 )
z_index = 55
texture = ExtResource( 2 )

[node name="Area2D" type="Area2D" parent="."]
collision_layer = 0
collision_mask = 6

[node name="CollisionShape2D" type="CollisionShape2D" parent="Area2D"]
shape = SubResource( 2 )

[connection signal="body_entered" from="Area2D" to="." method="_on_Area2D_body_entered"]
        GDST�   �           �  PNG �PNG

   IHDR   �   �   Z(c]   sRGB ���  �IDATx���oGvǿ�i�C�3�D&EY2���M�^E�6��>�C�=� ȿ���b��!v 	���)'�BK�\Ѱ(Q�Q3�{�������� g����T�W��Տ��s��O�{Xo��t1������.n���&�4�J���3���ϔӿ��i��s��w>�Ṭ�2�o�����U���ny�Pȫ�~������e�?�4�W�Pᨐ�@L�Ue�.nX˛-�򴝗-  Q��F�pT�d^2l* /G�g*3�\軎���6�� ҚI]�5�WY�.C��/�2Qu�L�URXo�z�	�������Lނ2�WY
����Mc��S&Y��'/�$`�{[�A'�����\Z��nGW����&�b1��6Q��[��Bc���^]��=��S���stv��[gOΝN�Ei��8��t"�������
i�j瓡�>l�֯Χ��b<�k'��TX�ͭk#Ɋ�T~ ��գt���\�שק���.�*�
i\K��������S�nq��Ĺ��p�PQ@�<���Z��O�<��K��ϳ�2�*��N����/n"D����k2/ڇ{x�uA0cUNU�h�Ɍ�F@P٤�4���KF���+���F��R�������cE!M1u�d^iTQ�T�#&
�@�����o��00�׬[���q�y��v�o����Ss�o����AQLƎ��vm:�P��
��+�wSm�<�D���� z@k7�]��ǭ��!VU@[��8E}j�ޑ�� ߃x�3��ѡ�N3+�	oE|��J��QU�*�I'Y���q��+�):DclK���T`]�"5y���֯:wuL��'�
O���t#`#Ce�"�2|+@�I��uDj02ԅ�r�lC�D��Z�n���@���5ɵ?`� f�W����؀W�*M�%�����&\(S5�$�A���L��#� b3I�j�<�E���`I�o���P��c�=���`��_5Ə�7�7�}�'��/���D� x���~"͵�ڃdU[��X��I���z �g��j6�k�7�� 0�hJ*����I�V��>57���z� ����ӎ-�L�å�� ��p�$Rf�&�3�vrwv�F�mG����1���Ss��j��Ɛ\�`��~���h� S��$�Wҵ�Q̾��.V�if&{l���k(��(o��1�aG�~�m����P��%��7���AL��/,�%ja헷�s"%f�0˔|g�n�T�p��Gg��Z��^Z�H����lh���__ǭOo�ν�}���Ӓ+ݣe ��+���TC���˒H���r6��8�� �:�� B��>��$�k�!B��C���T�����F�$��a�?�Տ�����#^���-m fi�u��g0��ƫ'��c
�ٕ6�O~ĭO!4���|��\f6�n��~�7���8,��+���G��� E�����?��!��B����G��#D�|C�9����}=*�e6Y@���g ����I6���i����0:��^��Wr[��ڒHD�o�0�?d��W ze�:c"��(4@�A1ՖAe�*&��˗�?���0���QN�(6��B_�X�q�2�`c��p<���U`5�~�㼼g{��ښO�Ɨ)x�ku'uFy@T��� X��r�]a��=z���Yib.�\\�/^|�����P�Y���6 �ԩ?k1s�e.�a\S��G��"�F� �O�G��E��^w�Nu0�h��fP��קc��zo�������>|�y�O
���/
e��9Fh� �h@����<�� �"@��};�}��p8������F�V޾��{U��^��ܣ��l��	�Q�<�����F+2�.���6;�w��w������ܶ��`��4�E����o�4?U�=��`���+a�T������nfj�~|��X��F#���/o�<����	 ���_��?����(t:Ɂ���w��@��^	(�Am�0օ�A�"#n��L�Z�:�����]Y�W�~��ݻx��s ٭ ���";'�}�深���+����d �	�O`k�^���� D�<�/��1�/�;����y`��� �H�A���^=�A·��͛��ll���E���~ ����ԑE��թ`��7�4#�ݬ��~{��ۂo-�&��{%�:@��y��t��PX�⮎^�U�`[������$���({E��{%\!�;�4��Ԅ�?��9M��k��g.]o���y�5���}:h�z�i�M��0M�d�W���D}ʃb���O��W�=��ȋ��p��S�����a;� "^�gf�c$ZUK�**����(�Epn ��I�Ҟtn�s�ە�=�c�17�0���2Py��k��AECڶ�ק3�w]"_?Í����ґ���'�U0���hG���{%L�Y�n��A)�ڻ����e�/����Ѝ�� ���]���s�W��Aj~|���C4���!�=�.�\�t&��@4��y��	t�#���d`0"<�ۣ14S�pI��@�HKG�������[s���){"�I'���=zV+d���p��;`��-� @���l�FDy�K��=�+�-�]���@�g#@ bwL͈�=�]$[�!�Q���^�X���2y%f×l��݋£|޼��fT�Gw���)�� ��S�!3����D�bb:�G�{%\c�n�j�n�8RXR�ļ� 9�HCb2O��B��m�Z��{H{��Kr�(;�<�7��`vz>�,M{2<�ha��Bs�Lb!<�G�Ө�ȵ��3<��J�Bk_ Y�f�����vl�h2��^�+�I��)~�Fi�<��=:{]Q" �9�0���J���8 �/�ӊ�v� �٠"_�Z^�i�XfH��G�Q����M���J��Z=$k~�����!��#����b{B����=�$S�)�@�Vk�"d�^�{l]��)����Xl��$��o�pn ,�Z?�Es��Z�w�d;Nx�þW�*�?Q	�u��P' �p(�K�1�Z^�<<�ܽbufq^*�������Z�r,�XL.�����ylu�� �7�Niױ���4�@�^��&x# ����T~��2(<@��æ}��#��6T���
�J�e<�!y��ino:����w>+_*���<1O�Gw ��|�,��F1��on������� �[▕��]a����{h5�g�Ǉ��:����-N#�IM��2yTtOe˧g/K�%�(���V�'8���U~��<Y3e�[��e�9P�{	E���ȯ��Q�Vs�� H�Pi�O�bkv�:���r�W� �FT���h,j�eH�B^�;�V OԠH-η*�E��o��!Tw��`�=3;��|7��2�˞��*?���?�?���t�yƎ�LQ>�i^�[�����?;텋�{�& ��+��}�����MZ�,k7�ŭ 4ީ�ܫG�)ص���/��cj>�73[/��J�I�ebօ��CY�uܨŅo������i�T���昻0-| =��+��B쨧��N�5(��O���ʇ�3��O6�ݨ�U��|���WO~e@Vk��K�Z�Q�C���z#����!�dy�n�W� LS��>���g��˯��J���n�8h�	c�*5������H���V~%�4�AɌ�T��Cajk@/?�|m��l�q}RjR\�|Qk"3�Vs	�VoD��.n(�>@��)�j!��������/�������4�]$�����D2UC����օ�����H���m���/?u_�2�H��K��w���]C��=�9v�\�wҀɼ�X��6�U�I���|@侤�4i�=��kՇ_0�D!�N�d�(�'?/�(�F�W� L�j.ES-t��0�9��W;�x���W~:t� ��z |�W��i�՚�˷'�Z ���h�EV�*�"��7/_ze�9E�,�ml��T��.��6�x��=��;�k�����(�(�W;�D��v�1�"?��w+?1����|�Μ��ؿ,�_���`�е��!s��Vb�7Y>*;�?| ^�����+��I55�e�U�76��ō�g\o�Q	*p�w��D��?^�[������&�^[��:'�
�>�
_g�g���w+�r�bra�Thl-B��¯�a|��'��by��ɯ��Ld�:�����FE
 $
�-D�.�=�a��y�Ց_)��w�Vv� `X���S�(�>��ҕ%�O;i�uʿ2�'��rM��5�Z�/Pztl��p�����K����Ǔ&_��+a YJ*��1��ti�,񵘨)eﷲt��=i(��廓_�}�ʄߞ��xP�fS��������W6{�x������w�Ҵ�������/�
�-X�y�:� D[�y�����. ��&6]��-Jwf��p{�R���ʹ�Y�������ƭ^��Q��J��4ތʊ(/߼�)��T#(��E2U�����n[�I�������3�F��L"hT����2���Y���c����F�l� '� ��>	:8x)�uK�W�	+CA�dx#������d�H�\+`�Q1��~� �W�f���[�_:���G�*����/_~�\�Q�䥬G��+���.O�W�)���3'�M���@���4�U�ґo��+�w#�� /߼|����n��Dk=@YF��,g߾,�ϟ��G[��P�l�����lr������; ���ž�w/4��K�'H�tL7?������?!zxYx���O5���w���AK`{=A����;���SSy���O�<�ޔ���1&�����?N�U��y���/�(~\��u�d5��fYe ��/O~�s
�g���yV�uܡ����lF��.l��~g��_G��|7�m�2�-��"d>��J�E�y�v����FPt�w�6��9E���WG��%Ey����w�� �K�W�`�.�_�*ODZ���|5�V��'(�/�>�/�ƫ�v�{Xl�ë�6�� ��|PU�|��m��r=��A���o*/߾|���ywh��؂�Z$olM��WK���q��1�A�篥<U����䗲��(���Xl����t����翋�A���<���/ߍ�ҶG�rK z 
�_c�R��y�����ˑ_���j��/*��1���廗_��b��&c�:y)~5�̃���ͱ�_-�� ���\O@���=:�|W0����*xQ�P�ߋOS/��˕_� �0-�^u��@p�:����|�|��-�)J�C.v$�T�BbLPՎ�
���^��˯���Uh	t`�>o���z�#(� �7�nZ�Zej�I�_��y�!�~ O*�E�O���ѡr '({�W�hS)�e�O�)�� 0�!R�hPi �x�Ry �x�a�l2�2j�e�����,'���4����2N�c�UF�  ��	<��Ht�E�q�	F�  �g� �F�)��>��Ϊ�y��� L�I���yF�bQq���{XF2��'���tW�,���g|I5 �St�}�<��X�x|�ԓ�X �������A�Əxd8��l�xD��$3>�yx�n H����Z���<��X@�����k��I�\    IEND�B`�     [remap]

importer="texture"
type="StreamTexture"
path="res://.import/Vorota-0004.png-c54c1166b5c14ae154cfeb672997e89e.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/Tilesets/Level1/Vorota-0004.png"
dest_files=[ "res://.import/Vorota-0004.png-c54c1166b5c14ae154cfeb672997e89e.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
            GDST              �'  PNG �PNG

   IHDR         �x��   sRGB ���    IDATx���mo\�y �[]��"rfj��%Q���	9�� ��t��.�XŢ�����o������~��n7�'@��$v*�J�R-�ݖ9*):����9sf8Cg�P���s�Q��s?o�~���ڎ1z�_���Z��^W*�G[[[k����:�___���t�ر��f�f;>k�7
�/:�����{�n�P��5������}��y������8��ګ�������y'���wx�7���Y�	��s���Z��'�.}u��ߋ���U��NA8}���sN�<�v��٣�X^��q���]\���b}�Q�G�/�v?;=K���������ڵ�#��k0�#"��^�����s�θ�x��&H�9�k�jDD����|�|"�O��7��-�=p..^�8�Q�Qܻ��ulc��:g��l��m�$���;�J/��������{�]g��{�&�{��O�yE�����#"buu=��^8�I@[���ֳ�C)�|�?�lDD|�᭡��J��5	���mxn�I+>�����l��?�����V"�O�����GV���������(<~���3�L.^<ׯq���툈�Ϸ�D��Ǜc�!�R$ I
���k#o��۩�'�Q������S'O��̀��E��@V������}�K^���5{t�-	H�?���,[	80�-�$�� �T���奈�]�ժ�0d[�;���Gq��;>�7	�8�`P_�����d��;w����|[% "bs����Q;�{zVc �q{��7h�ժq������_�#ɟ���a��7
�|�d�~�]Q�|��Lr���~��������ٿ׫033�q�k��Z�Q�;� �-�ƞ $��4��7������3�4`�[���������7�ދ�t���?ȴ�n>���z~~>ff��7��yT*s{�v�����㥗�����Z��g��$ ��ժq�'����׻�I��) ����?]#����n��AZ�ٖ{��P4�SSS����_[k��� ��
У��R����/�m�pjjj��	��?�$����������w���j�X�_�����m݁Q�7p� �V�ߡt��G������n�%�7�}%)�����Je.���oED�����I�ln>�������R���R��
@6��^���]D�69��j@��S_lk���_ē���Y �ݴ޳���N�����ر�@/�R�����[`ff�m����|ܹs�p��(���]��߯��?y=n����y�X+�g������=K�|E;������G۪ ��7���ў����XoĽ�by�F�<�����ys�q�������%�?�l�pP���i�����b~~>U�~ Fe"* )����ݪ�n����2I�����m��?,�k���{��Qܽ�Mx.^l�FƧߙ� &�
��������Yo�����x�MD1����������䓀a�W}v����(^T()�[��ވ��BLOϴ��gG�MT��۽=ۓg�Rt�;w��w�Z5VVnu��O�O� e���x�h���{-����)��e7Jϓ�׫�!�*N�O�x.����Dġk�ޏ'����g�� ���T �~�����~�࿲r+���퉨t۝o��_��o""�+_�R��1i���٣���p����:��l���`�I�D�/d��E (�R' �Z�3���,�o����G��������-Z�'k�%��%�n�?��&I+��x����n�t�_<�[`f�xe��'E��gffbs��
0�J ���w��c�R��,iu�ѿ�-�|�L-���<ٝ��V�=ھ(O�����l��V����A���vDD\�~#.^��j��<333���Wbffz���ɡ�߾����/���fln~�z����w`XJ� 䭮�;Z�E��g�Z5>��.8	R�/�77w45&��u]���cvJ��	Av�a�i)ᙙ�~�F�弴�B
���y��o�Q����t����x���VǱ���Z �X�"XY��ث
�O����/}sǿY�UK���n�i+�G�Gm[w�I?A��9���S੓'ڞ!ߍQt�Ç�����bs�qlmme��Ah�'�ff���~�Jlmm���T��L� �R$ �Z%VW���,%y�	����-�W4�?�M��EՋ�^ [[[���whkkk;=cJ ƥ� �eu��W뿌�]�/`�+�������������>j�GȮ0;7�
�SSSq���x饯E4� >h�_z�kq���V�������R% �Z96硻�d`q����&SSS��xsy���2�)	ؾx�|ln~����ӭ��� �J���f�ߋ�L��@��N�l������9m�q��H���f��� �Ji��W��^�wP�J�n6���o�lRF�-�Z��rVWף9mn�6�)��_~1VW�۞1U�? �R�A�y)H{+ߔX�j�XY�G"�5�$�����l�?��$Ģ{�`zv�q{P��E����
p��RD�J@sv�0��� �j�G켢_R��?�"A��n���j��PRt�333Q��>+���=(��@>�g���e6��<�����i��^{�
�� ��)E��de����K����*����՟��~�۸{�^�>}*"b���^U����]W�;{�Tܺwo,ﳋ�����ވ�͍8~�X[`L��
@��Ʃ	@?�A;+��W��o�V����\4��h�=�ו�\4�O��/Hz��y��`=��)	�w�A�J��d�*��|�Z�`/��U6E���NR��88&&���ʭ��ֲ�++�����˹�`>	赞~�����)H�ߤ�833�]'�cE��^{5^��C��a)� 2� g�--}0.�I �u�FJ��F^Z�v\��;�V�辙O٥*@��M�ϔvL+�5����jUI�r����v����͛�M䅅s��ݎ�&{� �t6)�oԏ2l�3�٣�� �k#�T����>kЊ���Tk]�����T沋 �$`{vv��� 0~��	��^o�[]�G�V�ju���U v��箭=�0��K��������~��1���J�ٝ�"��@e�OF��_��+s���Mϰ����
�����j��/���L�$`��k#*�9� ��� ������l�O���@>�'�^p(I�E�D [����77w��,/߈�|�Km� �U	(Z��(�G<IpR"0;7����N�x.�H^y�x�7
����W^)�x;�����m��77[�R����盃�>���//*�J�$`?��b�D`����ֺssG���q����$`ܕ�$���=:�JRI<���o���'A��鎕 �?�oߝ�g������ϟ��յ}	�㴺Z���z\���=u9��������}V?�?I	���t�9s�cu��+�$�����`D���gΜ� 0V�� D<Y�oX���U�"���n�*�i�'������m-��B933�Ld+9������v8y�c� d���?l�N�h������xa���l-_�~���϶�������$n����/v��|���o�  c5P�f���4�࿗Yeqt�}������vĩ�mg���I���/�=��G�u zI��ES����u(��(-��F��wޠ��������]G����̙Ӧcն@�^o��]M�KktK�G�Z���������٣�� R�|�����+�ȏ����Oʮ��v��>�4@`�ں �?��S�ߥO��b�<�Ŏŀ"�?`�� �����'����iW���ʋ�1U/�� �� �? �R8`��7��w�{Z�~?I��ƣ��1�1 ���]�d���p�1 ��\������\���o_�ju� ���>�'z%ݶN-�q�D����L���w�Z�'N<��~�F���9=K�o߾k 0V�Y�����3��X�$�`~0`ѽ��Gj�^�ެl�9s:�չ��܌k�>(��(�lK�ڵbi���V�^_�۷�0j�Z�w��sg��6J/È'�>���2U �*;umlmmEDt���_���������kz�lU#��V���Q9��Uk���,�^��)�w;&]'"v�����[	�(g�m�o߾�.}u�j�j��ޯ�ر�H�M��r��Q����>n�Y %0�oߎ����F?~������<����^{�㳇?���|��p�ʕ��5�ќ���J+���[��Rp���M"j�j��ƭL����qt��`z�|��_�Xp�����LMME���8�;"M������Pѳ5��������
@/����� D��
P�
@>(ZV7m\�J@�
����k �Y�}�v�g��
@ٶN�m	�}�y�?K ��� T��=-D�~�Ds��G�Gm���rT z��fWF�)z����8~�X+�/-=����} ��f�������� ��w �yse�K�^�~="b�U�Z�++��^X8���,�^K��+e�d���������t�۷�T Μ9��\DDv@� �Z�)����U'�3"�le{.��*�: �Zy���!m	��z��J��+ ��t��J@j�����G<�L�,��#�<[z�Iz6��@	�����G����z��>�'�g���l45WL1��J^Z0b��������OΜ9�� �ԾU v3��i��F~w�Q���'����#"67?�Ze��l% �0*U ���z���@�~��JI�~���}� �q���&����q������Is+�gbi���v�혼� �S����":� �T�
@� ��	(:��^U��W��^�j�}��4��ٲ��= �M�?�s�|% ��7�����l�  �ӵ�����s�b�*�>j�J��km�])�����|ܪDt��777�N���J�Y���-��q��g���m�gd� �������W�uTΟ?;�j@su�����
8+;X�c Rw� �y����It�8�F6`�� )	�|y)"R�@%VW�v]��l����ӌ�~�������I@�	��] �2���}9Z��ͨ� ƭ� ����V;[�� }��Ra�}e�Vk]���@VQ�?�?���q��8}��F����h[p�D T�Ͽik����W�Txo�H��["P֠_��{��2I0���A;+��6 �����עR�k�Ϟ]�}�+���ϴS0-C��vt[ￗ�z#�FkYܢD���8`{i���d �� ��`�K����ʭ�x����ʭ���c�-_�G���{��l����V����@���#"��
��e�[�>P&�� �����H�w��e�uQ7�0�����:v�X��~�iZ�??���%�`���0ɷ�ggg;Z�e��h4����16�n��X�* i��8w�+
�٤ ��"u��@e���xy��/^n��ۿ��I)��I����>o�?�� ��� �n�����kkO��K�������{��*>��8v�X��}��S��)��_�y~7ǁ�����z�XLB��L��$ )8g�}�7�ŀ�@�1 �ڎ8���[3߼����[����}��pn��#��_�şK�@�&I)�|�?�9���o�oU*��I�(������cBЯ�}�[q��d��k4�n����|��ڋ/��6 R� I�/��Ÿ�Q�� �x���ے��g���������{����;����L		@?�})�~�U����i2� ;�o��ے�� �&cO �Q�w߽��Y����¹��< �R�`�N�<)� �Ci�Q���R�I�Z�J����ɓ��.� �Si� ��V�� X���ٳg�pG��	��z� �*M0�j�6���)M0L�����זZۤ�OK� vR�1 Ö��wֱ߽�]�.�Ibp {Q��ܹ��rݔ��܊z}������"b���/� ��"�O����T*Q�TJ��5�ay�����^�����X�9 Dd�z���X�����r�(�jոu�v)��{��jX�+� ���� ^T2�)�w;�׹ل!L�Vݗ�uX�V�V�8��Ϝ��'m�����"�;����|�?��p`�(�/^]�� T���W�u�t��?�{��V����?�ӎ�� ��ￕ��}�] ��#"�E~/���s}]���":�j�>���[���ì�
���	�������z�w��>|��{���0H ߋn�V������Q�����mG�w�U�������	Ǐ��Z�OS����^�-���<�[ ��@.1��R�~*����������dz��W'2�GLf�<=�N,���#��YX]��-��S�/�-��4�~�Q� ��`��z�$�M j�f�~?��y��i�{�""�ȑ/����{���o�4^{�UI 0r�] ��t��u���[bp����Z��/A:{��^oo-�����ڏ��kOEH�⍍��\f;���q������sv�i�� �ҵ`��w����U	H�E�V�����z{�O���?r�Hlll���F9rd�KlGD,-����k� ���x;\�cwu|�^>?n��,_�|9�^����2�A����1�m{�^��Q	8��Ъ�Zu���wR�?�L%����>��^������L�N�m�Kr�v=>����B:����9�c�z���?6����赒_D�E�����˗�""u	4%�����l����{��*.]����e���J�����������o���|cc#nܸ�jQolll9r$.\X������������f���XZz!666������R��6��|).\X�Ǐ�����g��z���F,..����XZz!~�_v��bc�_#"����]�\�?0]����E��A����_���џҗ//��WVne����������Ow�ދӧOED�z/�f�=>x��R�?��?�����Q#"ڒ�����޽q���ƍ�c~~�L?��wQ�̵���;w�Ώh�ox���X\\���7n�}���#G�ڵ������ȑ#��g�=��s�N���GD3���ߏ7nƳ��a|��o#���_����ڵ���G��s���V򑾏�C�?0.=��h��cz-<셅�A;9w�lk���Ζ|�V����\4̀�~��u�2W�L�r�����͍��������/~�����^������������F\��~��T^϶�#"���[�}��e�<�����t���ϟn}~�Γ����������>�����_���}��hOc ��pD�k��[��Z=��l�V+��r��yD�:�m�_v����V��Ͽ�|�0��ŋ�Ӊ��������G��ƃZ�SK<t�ܹіd�ϿϷ�?~�%�=���~��>�~��=���w�g�Ο�=Z���J��&fg�~�h<ڿ)�������K{��;OZ~��UoQ�___/8r��������6�V���X���ֿY ��<�����(*�nW���.��5�LMMm��f_� �����툈'Nz����� x�-حo|㥶*�(���^G��V�, F�-x���b���M�#	�U���e���\�pҜ8q�mL  ��c!����l��˹���K�>wP��t:q�ĸoa������0w�ll��B�C�%��ŋ���_�|�^����)���8���wˉ'�G?�Ѯ�!�_[`�Ls���G��Hj���'�[�{
����e�{���% [_<��Mr��fmm����k��4��u���e3����Jew�d��-	��ڊx������� Ƣ-XX(�k?y��e����v��& �
+ ���9�WPt|7��L#p�t����T	 ���P̧��g��ַ���w?�L��Z�vk  0nm	�����0�;s6N}��q�歞+:������������jul��n�����x��-��c(� {����t���A �$m	@������777{~�]$����������t�D��2(� m��[)�g�	d���Gq  �IDAT��0� �0n{���ʿ��Ϸp'���-��%	�(�VP��L�������ªAZRx���n�Q	 �q���f�|�R4_�E�,���@�g/=����Է��J�1��;)$ L��Ͳt���Z������~��X�}+�s{T�ոr�ݎ�.,�k��������ժQ��E�Zٱ�0n�JehA~mm�j� ���f�~����c'[_,,�뫕��y���[ߎS�ӟ��׹e��vQ"�o@W) �l�:�����<s�����I�E��! �Ek�ܙ��8S�϶����"�Ɉ�씾n��e��~cGA ��
@*ק��S?}�������2�X`�{��y��Z���+W�m}�O`�X���I��V�����͑�Sg���������׫m��w�����f  P6�'��M}t��� �^���7W�4��Lj��P�8} ʪ� ��g�_����4��@LX�q�Z�� �V�_��Ocfff�v��ga�\\��n����""2��4��[��f"�J 8Hں R=�Y�y���?߷߭??%E��?���q��8}����(_�8������i~ٲ}>����ca��1�����#"*�����F��Q�.� ������g�+k� zku��'=语����(_��u,�[���1� ��-  &G[0��x ` ��$ �]�>��z�q� �]��A[�Z� 0Y���� ��d  <����� K��a%�	 ?]  �����ů
  �5�
�� �2��^_�e �)L �#�� @y�P�U{� ʧ� ���=]��j�� ������h�^��YD� �O������u��u8"bu��т_]�G�ڻ�_�V�ʕw;>_X8Wx|�^�Z���ZT��=W ��9���j%~��7Z_,,�뫕�-��|�R��  F�p�����J��53@����: ��O�?���2�� ʪk`q 8�:������y��Z["p�ʻ}�  ��pч�F���vR�ף^�F�Z)���k  ��0��>Xo���^�9�oa�\ܼ�"	 �1*�����ꓹ��q�}� `�2Ko�_�������W��k*  �Y[@Z�/�Yȯ	����֟�O�� �u8�����O*� ��Z����R~��|� ��pD�k��[��< L�V@��\���w8"��& ���0 ppI  �)$                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    �	��::B�#'    IEND�B`�  [remap]

importer="texture"
type="StreamTexture"
path="res://.import/level1_tileset.png-ebaf426714cf87313ead9c65229c7304.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/Tilesets/Level1/level1_tileset.png"
dest_files=[ "res://.import/level1_tileset.png-ebaf426714cf87313ead9c65229c7304.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
 GDST`   `           +	  PNG �PNG

   IHDR   `   `   �w8   sRGB ���  �IDATx��]AKcI.%��a�<r�̲ಈ�MO�q��o�8ǹ�-VX��`D���2�����~�%�dF�W�KUwUuwU����� ���+  ��ſ�(˷�ߊb��#�}���Q_P�)aRpem#�� ��}4B)b~���  v󼛄`����{��6{�r���b#���޿����bdtI�V�q��̐�	�KY�+����_����G<P:ϻ��������W23PS��}�ʟg=�k�2��oq�i�LA�����j �w���a#�3�k;�+�\1@v���R-Z��~V���
�6-�B����c�,hV�X?���d{��w����tzo]+poHt�m䗤�N��=c�Z/D�m�G��y��G���@�"6K��ʣ����M��7��g=�ld�6l��͵�d1��c�#]����
�f�>�$�d�>�36�)Ƿ���j �w�YϘNI�/�%�T��VP~ʹ]���9���_�o�K�@�*�nE��C�TFN���(n�
p->y�4'��`L����� lZ)��r���@n�ɭ�~@.���pw��6���meE|$iKQ�r�<e���{9����F>g�hA�,	�ճ$4Nh�o�В�C|�cB�A��q
�'~��Cq�r�Ǭ����݅��V�.;�[N1�!|xS��1t��fv]��TudI�e�܇i�(z]M*�mg�<�Y�R�u�S��Te�fp��]�oժ�,�|(cԃ�
yy�5���T�>�Tד�l3����wK��ބ�\�Fl2�Z�c�ft��}�:��($=V�	����.���/0�~f|��a|��r����^�Td�r1�Pe�)����fI� L�8�~��ǋ!L��6�M�({|��x��~�X�_�N6�pW9/_We+�8�N���2�K��t��
w�AW�	&GVEp����Fh��\��&#P#���
��#�RB�*�~���|%v�(�F�d��N� R��e�j���\���.p6!�f@��&4�T���#�����+�#�K�����g=2P~�����.O��������.�Q�O����tz�#=땂
�����f���'"��*e}�Z�!���7UO����.�Q��|��rC>nJU> ���+_��c�Tc*����+�P�����,��|^�A��
©�-¤|w&ؔ���g��b���p1�YT1��Tg�>ڐ�]��.#p���r�#8;�3W��g7��0���(_�E�;� q�N:��.Gp���
C�3A�|U�Ԡ�ܗ˅�4u& ��")\V��
�!� �j
!i&�Z�V�k�(t?ȅ�8;]lU������>�|������)����Ş� �bD*?$M�U��|�v�a��`9Rc�������8�v���t�#$F@Y.�,[��?������8��>F@Y��������  ��<��Djrpv�7c:5t)�4��S�@
w6��l6{��/�Y����q&p���̈́��Oi�g>���-��6���GPF�(�5�}��R��?`�o��#�I���ݑI�u;X��t�F�u$yFl�|uTE Е��	�=��{��~�>��������rj�DL�fQ����|�	�G���P#����.�]�  6U'j2����h�? �U��N=�$m�\��Q� �㋟L�_�(�6���z��U� �T>�e��uY��}�}Z����?  ��O���k�4�����O]��.�G?Udq�P��j�;5·�?��J�P�������`oi����6k�I]�凜���.ٱO�|��S��\\#}�R|xߵChE��(?E@�nh��Mh�c�ףK����"0�$��}PnɊT�Kɒ������BC��(/��UO��uB��ln��MS:R��\�~ڐ�?@���J
՗J����u��?@�� 	�7�*%l���k��~� V;�F����VC�B���� �ۘ��OŁڟ��F!�y�T�u�7�� i�-U�4������p �<�ɽ���ɟ`{xM�\ޅ6�H�� ���L��O[�}�@Y����|S{�m�w��LصFض�Ӈ?��(�uvA�3���1���#v���+�-����|�~z�����q�kN&���D~�q:�6��0����M�?? ɛ*�d~ �?�,��7l��T������h�n�~�tIӛ��|�M�\�oP�9Bj��     IEND�B`�         [remap]

importer="texture"
type="StreamTexture"
path="res://.import/lvl.png-04da9d90d36d937886ccb1aeb366b1ef.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/Tilesets/Level1/lvl.png"
dest_files=[ "res://.import/lvl.png-04da9d90d36d937886ccb1aeb366b1ef.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
    [gd_resource type="TileSet" load_steps=2 format=2]

[ext_resource path="res://Assets/Sprites/UI/UI_tileset.png" type="Texture" id=1]

[resource]
0/name = "UI_tileset.png 0"
0/texture = ExtResource( 1 )
0/tex_offset = Vector2( 0, 0 )
0/modulate = Color( 1, 1, 1, 1 )
0/region = Rect2( 0, 0, 64, 32 )
0/tile_mode = 0
0/occluder_offset = Vector2( 0, 0 )
0/navigation_offset = Vector2( 0, 0 )
0/shape_offset = Vector2( 0, 0 )
0/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
0/shape_one_way = false
0/shape_one_way_margin = 0.0
0/shapes = [  ]
0/z_index = 0
1/name = "UI_tileset.png 1"
1/texture = ExtResource( 1 )
1/tex_offset = Vector2( 0, 0 )
1/modulate = Color( 1, 1, 1, 1 )
1/region = Rect2( 0, 32, 64, 32 )
1/tile_mode = 0
1/occluder_offset = Vector2( 0, 0 )
1/navigation_offset = Vector2( 0, 0 )
1/shape_offset = Vector2( 0, 0 )
1/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
1/shape_one_way = false
1/shape_one_way_margin = 0.0
1/shapes = [  ]
1/z_index = 0
2/name = "UI_tileset.png 2"
2/texture = ExtResource( 1 )
2/tex_offset = Vector2( 0, 0 )
2/modulate = Color( 1, 1, 1, 1 )
2/region = Rect2( 0, 64, 64, 32 )
2/tile_mode = 0
2/occluder_offset = Vector2( 0, 0 )
2/navigation_offset = Vector2( 0, 0 )
2/shape_offset = Vector2( 0, 0 )
2/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
2/shape_one_way = false
2/shape_one_way_margin = 0.0
2/shapes = [  ]
2/z_index = 0
3/name = "UI_tileset.png 3"
3/texture = ExtResource( 1 )
3/tex_offset = Vector2( 0, 0 )
3/modulate = Color( 1, 1, 1, 1 )
3/region = Rect2( 64, 0, 32, 32 )
3/tile_mode = 0
3/occluder_offset = Vector2( 0, 0 )
3/navigation_offset = Vector2( 0, 0 )
3/shape_offset = Vector2( 0, 0 )
3/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
3/shape_one_way = false
3/shape_one_way_margin = 0.0
3/shapes = [  ]
3/z_index = 0
4/name = "UI_tileset.png 4"
4/texture = ExtResource( 1 )
4/tex_offset = Vector2( 0, 0 )
4/modulate = Color( 1, 1, 1, 1 )
4/region = Rect2( 64, 32, 32, 32 )
4/tile_mode = 0
4/occluder_offset = Vector2( 0, 0 )
4/navigation_offset = Vector2( 0, 0 )
4/shape_offset = Vector2( 0, 0 )
4/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
4/shape_one_way = false
4/shape_one_way_margin = 0.0
4/shapes = [  ]
4/z_index = 0
5/name = "UI_tileset.png 5"
5/texture = ExtResource( 1 )
5/tex_offset = Vector2( 0, 0 )
5/modulate = Color( 1, 1, 1, 1 )
5/region = Rect2( 64, 64, 32, 32 )
5/tile_mode = 0
5/occluder_offset = Vector2( 0, 0 )
5/navigation_offset = Vector2( 0, 0 )
5/shape_offset = Vector2( 0, 0 )
5/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
5/shape_one_way = false
5/shape_one_way_margin = 0.0
5/shapes = [  ]
5/z_index = 0
6/name = "UI_tileset.png 6"
6/texture = ExtResource( 1 )
6/tex_offset = Vector2( 0, 0 )
6/modulate = Color( 1, 1, 1, 1 )
6/region = Rect2( 96, 0, 96, 96 )
6/tile_mode = 0
6/occluder_offset = Vector2( 0, 0 )
6/navigation_offset = Vector2( 0, 0 )
6/shape_offset = Vector2( 0, 0 )
6/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
6/shape_one_way = false
6/shape_one_way_margin = 0.0
6/shapes = [  ]
6/z_index = 0
7/name = "UI_tileset.png 7"
7/texture = ExtResource( 1 )
7/tex_offset = Vector2( 0, 0 )
7/modulate = Color( 1, 1, 1, 1 )
7/region = Rect2( 192, 0, 96, 96 )
7/tile_mode = 0
7/occluder_offset = Vector2( 0, 0 )
7/navigation_offset = Vector2( 0, 0 )
7/shape_offset = Vector2( 0, 0 )
7/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
7/shape_one_way = false
7/shape_one_way_margin = 0.0
7/shapes = [  ]
7/z_index = 0
8/name = "UI_tileset.png 8"
8/texture = ExtResource( 1 )
8/tex_offset = Vector2( 0, 0 )
8/modulate = Color( 1, 1, 1, 1 )
8/region = Rect2( 288, 0, 96, 96 )
8/tile_mode = 0
8/occluder_offset = Vector2( 0, 0 )
8/navigation_offset = Vector2( 0, 0 )
8/shape_offset = Vector2( 0, 0 )
8/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
8/shape_one_way = false
8/shape_one_way_margin = 0.0
8/shapes = [  ]
8/z_index = 0
    [gd_resource type="TileSet" load_steps=11 format=2]

[ext_resource path="res://Assets/Sprites/Tilesets/Level1/level1_tileset.png" type="Texture" id=1]

[sub_resource type="ConvexPolygonShape2D" id=1]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=2]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=3]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=4]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=5]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=6]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=7]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=8]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=9]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[resource]
0/name = "level1_tileset.png 0"
0/texture = ExtResource( 1 )
0/tex_offset = Vector2( 0, 0 )
0/modulate = Color( 1, 1, 1, 1 )
0/region = Rect2( 0, 0, 32, 32 )
0/tile_mode = 0
0/occluder_offset = Vector2( 0, 0 )
0/navigation_offset = Vector2( 0, 0 )
0/shape_offset = Vector2( 0, 0 )
0/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
0/shape_one_way = false
0/shape_one_way_margin = 0.0
0/shapes = [  ]
0/z_index = 0
1/name = "level1_tileset.png 1"
1/texture = ExtResource( 1 )
1/tex_offset = Vector2( 0, 0 )
1/modulate = Color( 1, 1, 1, 1 )
1/region = Rect2( 0, 32, 32, 32 )
1/tile_mode = 0
1/occluder_offset = Vector2( 0, 0 )
1/navigation_offset = Vector2( 0, 0 )
1/shape_offset = Vector2( 0, 0 )
1/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
1/shape_one_way = false
1/shape_one_way_margin = 0.0
1/shapes = [  ]
1/z_index = 0
9/name = "level1_tileset.png 9"
9/texture = ExtResource( 1 )
9/tex_offset = Vector2( 0, 0 )
9/modulate = Color( 1, 1, 1, 1 )
9/region = Rect2( 64, 0, 32, 32 )
9/tile_mode = 0
9/occluder_offset = Vector2( 0, 0 )
9/navigation_offset = Vector2( 0, 0 )
9/shape_offset = Vector2( 0, 0 )
9/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
9/shape = SubResource( 9 )
9/shape_one_way = false
9/shape_one_way_margin = 1.0
9/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 9 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
9/z_index = 0
10/name = "level1_tileset.png 10"
10/texture = ExtResource( 1 )
10/tex_offset = Vector2( 0, 0 )
10/modulate = Color( 1, 1, 1, 1 )
10/region = Rect2( 64, 32, 32, 32 )
10/tile_mode = 0
10/occluder_offset = Vector2( 0, 0 )
10/navigation_offset = Vector2( 0, 0 )
10/shape_offset = Vector2( 0, 0 )
10/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
10/shape = SubResource( 1 )
10/shape_one_way = false
10/shape_one_way_margin = 1.0
10/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 1 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
10/z_index = 0
11/name = "level1_tileset.png 11"
11/texture = ExtResource( 1 )
11/tex_offset = Vector2( 0, 0 )
11/modulate = Color( 1, 1, 1, 1 )
11/region = Rect2( 64, 64, 32, 32 )
11/tile_mode = 0
11/occluder_offset = Vector2( 0, 0 )
11/navigation_offset = Vector2( 0, 0 )
11/shape_offset = Vector2( 0, 0 )
11/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
11/shape = SubResource( 2 )
11/shape_one_way = false
11/shape_one_way_margin = 1.0
11/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 2 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
11/z_index = 0
12/name = "level1_tileset.png 12"
12/texture = ExtResource( 1 )
12/tex_offset = Vector2( 0, 0 )
12/modulate = Color( 1, 1, 1, 1 )
12/region = Rect2( 64, 96, 32, 32 )
12/tile_mode = 0
12/occluder_offset = Vector2( 0, 0 )
12/navigation_offset = Vector2( 0, 0 )
12/shape_offset = Vector2( 0, 0 )
12/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
12/shape = SubResource( 3 )
12/shape_one_way = false
12/shape_one_way_margin = 1.0
12/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 3 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
12/z_index = 0
13/name = "level1_tileset.png 13"
13/texture = ExtResource( 1 )
13/tex_offset = Vector2( 0, 0 )
13/modulate = Color( 1, 1, 1, 1 )
13/region = Rect2( 32, 0, 32, 32 )
13/tile_mode = 0
13/occluder_offset = Vector2( 0, 0 )
13/navigation_offset = Vector2( 0, 0 )
13/shape_offset = Vector2( 0, 0 )
13/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
13/shape = SubResource( 4 )
13/shape_one_way = false
13/shape_one_way_margin = 1.0
13/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 4 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
13/z_index = 0
14/name = "level1_tileset.png 14"
14/texture = ExtResource( 1 )
14/tex_offset = Vector2( 0, 0 )
14/modulate = Color( 1, 1, 1, 1 )
14/region = Rect2( 32, 32, 32, 32 )
14/tile_mode = 0
14/occluder_offset = Vector2( 0, 0 )
14/navigation_offset = Vector2( 0, 0 )
14/shape_offset = Vector2( 0, 0 )
14/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
14/shape = SubResource( 5 )
14/shape_one_way = false
14/shape_one_way_margin = 1.0
14/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 5 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
14/z_index = 0
15/name = "level1_tileset.png 15"
15/texture = ExtResource( 1 )
15/tex_offset = Vector2( 0, 0 )
15/modulate = Color( 1, 1, 1, 1 )
15/region = Rect2( 32, 64, 32, 32 )
15/tile_mode = 0
15/occluder_offset = Vector2( 0, 0 )
15/navigation_offset = Vector2( 0, 0 )
15/shape_offset = Vector2( 0, 0 )
15/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
15/shape = SubResource( 6 )
15/shape_one_way = false
15/shape_one_way_margin = 1.0
15/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 6 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
15/z_index = 0
16/name = "level1_tileset.png 16"
16/texture = ExtResource( 1 )
16/tex_offset = Vector2( 0, 0 )
16/modulate = Color( 1, 1, 1, 1 )
16/region = Rect2( 0, 64, 32, 32 )
16/tile_mode = 0
16/occluder_offset = Vector2( 0, 0 )
16/navigation_offset = Vector2( 0, 0 )
16/shape_offset = Vector2( 0, 0 )
16/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
16/shape_one_way = false
16/shape_one_way_margin = 0.0
16/shapes = [  ]
16/z_index = 0
17/name = "level1_tileset.png 17"
17/texture = ExtResource( 1 )
17/tex_offset = Vector2( 0, 0 )
17/modulate = Color( 1, 1, 1, 1 )
17/region = Rect2( 0, 96, 32, 32 )
17/tile_mode = 0
17/occluder_offset = Vector2( 0, 0 )
17/navigation_offset = Vector2( 0, 0 )
17/shape_offset = Vector2( 0, 0 )
17/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
17/shape = SubResource( 7 )
17/shape_one_way = false
17/shape_one_way_margin = 1.0
17/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 7 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
17/z_index = 0
19/name = "level1_tileset.png 19"
19/texture = ExtResource( 1 )
19/tex_offset = Vector2( 0, 0 )
19/modulate = Color( 1, 1, 1, 1 )
19/region = Rect2( 0, 128, 32, 32 )
19/tile_mode = 0
19/occluder_offset = Vector2( 0, 0 )
19/navigation_offset = Vector2( 0, 0 )
19/shape_offset = Vector2( 0, 0 )
19/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
19/shape = SubResource( 8 )
19/shape_one_way = false
19/shape_one_way_margin = 1.0
19/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 8 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
19/z_index = 0
20/name = "level1_tileset.png 20"
20/texture = ExtResource( 1 )
20/tex_offset = Vector2( 0, 0 )
20/modulate = Color( 1, 1, 1, 1 )
20/region = Rect2( 96, 64, 32, 32 )
20/tile_mode = 0
20/occluder_offset = Vector2( 0, 0 )
20/navigation_offset = Vector2( 0, 0 )
20/shape_offset = Vector2( 0, 0 )
20/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
20/shape_one_way = false
20/shape_one_way_margin = 0.0
20/shapes = [  ]
20/z_index = 0
21/name = "level1_tileset.png 21"
21/texture = ExtResource( 1 )
21/tex_offset = Vector2( 0, 0 )
21/modulate = Color( 1, 1, 1, 1 )
21/region = Rect2( 96, 96, 32, 32 )
21/tile_mode = 0
21/occluder_offset = Vector2( 0, 0 )
21/navigation_offset = Vector2( 0, 0 )
21/shape_offset = Vector2( 0, 0 )
21/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
21/shape_one_way = false
21/shape_one_way_margin = 0.0
21/shapes = [  ]
21/z_index = 0
22/name = "level1_tileset.png 22"
22/texture = ExtResource( 1 )
22/tex_offset = Vector2( 0, 0 )
22/modulate = Color( 1, 1, 1, 1 )
22/region = Rect2( 128, 96, 32, 32 )
22/tile_mode = 0
22/occluder_offset = Vector2( 0, 0 )
22/navigation_offset = Vector2( 0, 0 )
22/shape_offset = Vector2( 0, 0 )
22/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
22/shape_one_way = false
22/shape_one_way_margin = 0.0
22/shapes = [  ]
22/z_index = 0
23/name = "level1_tileset.png 23"
23/texture = ExtResource( 1 )
23/tex_offset = Vector2( 0, 0 )
23/modulate = Color( 1, 1, 1, 1 )
23/region = Rect2( 96, 0, 64, 64 )
23/tile_mode = 0
23/occluder_offset = Vector2( 0, 0 )
23/navigation_offset = Vector2( 0, 0 )
23/shape_offset = Vector2( 0, 0 )
23/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
23/shape_one_way = false
23/shape_one_way_margin = 0.0
23/shapes = [  ]
23/z_index = 0
24/name = "level1_tileset.png 24"
24/texture = ExtResource( 1 )
24/tex_offset = Vector2( 0, 0 )
24/modulate = Color( 1, 1, 1, 1 )
24/region = Rect2( 160, 0, 32, 64 )
24/tile_mode = 0
24/occluder_offset = Vector2( 0, 0 )
24/navigation_offset = Vector2( 0, 0 )
24/shape_offset = Vector2( 0, 0 )
24/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
24/shape_one_way = false
24/shape_one_way_margin = 0.0
24/shapes = [  ]
24/z_index = 0
25/name = "level1_tileset.png 25"
25/texture = ExtResource( 1 )
25/tex_offset = Vector2( 0, 0 )
25/modulate = Color( 1, 1, 1, 1 )
25/region = Rect2( 192, 0, 32, 64 )
25/tile_mode = 0
25/occluder_offset = Vector2( 0, 0 )
25/navigation_offset = Vector2( 0, 0 )
25/shape_offset = Vector2( 0, 0 )
25/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
25/shape_one_way = false
25/shape_one_way_margin = 0.0
25/shapes = [  ]
25/z_index = 0
26/name = "level1_tileset.png 26"
26/texture = ExtResource( 1 )
26/tex_offset = Vector2( 0, 0 )
26/modulate = Color( 1, 1, 1, 1 )
26/region = Rect2( 160, 64, 64, 32 )
26/tile_mode = 0
26/occluder_offset = Vector2( 0, 0 )
26/navigation_offset = Vector2( 0, 0 )
26/shape_offset = Vector2( 0, 0 )
26/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
26/shape_one_way = false
26/shape_one_way_margin = 0.0
26/shapes = [  ]
26/z_index = 0
            GDST              e  PNG �PNG

   IHDR         �x��   sRGB ���  IDATx��ݱjW�3bp�J`p�K��گ��0���ï�zӧV�*�i���Rx7�4&�Z�Z���L�3������h�.Wח33�͏���L��5�z����ë�3�����/f�?����ۻ����-Wח��Bjs��I��^��n �?c� 柱��� ��Ez ��'  @!  
	  PH  �B    ��   �  ($  @!  
	  PH  �B�t�ĕ�=�~;��2�,�/�	  ���3��&�z�v�e�Yf_�  ($  @!  
	  PH  �B    ��   �  ($  @!  
	  PH  �B��,3��p���S������������O)��KI�`�Y�O��ë��=T��Ͽ�[�u��V��?� �d�Y�O�u�|�=6	�k�������n��{�=$�����o����;  PH  �Bkz</���I�u}y�����~��������I��n��Oz��oߜ���x  �  ($  @!  
	  PH  �B    ��   �  (�N������ן��!�z��Ok�?a�  @��y<���n��?�������OK��^?���< �B    ��   �  ($  @!  
	  PH  �B  Z��y���Lo���w��[��������  
	  Ph��ef6�Γ�z�T�~�_S�/3s���)<�����CO�?c�i��'l���Ez�~Ho`n&�����Sk�/�~�}!�k��������/��Ɲ޿�g5���O���  ($  @!  
	  PH  �B    ��   �  ($  @!  
	  PH  �B��IVO!�{z�v�e�Y�_�  (t1�gr7�M������?���̾�'  PH  �B    ��   �  ($  @!  
	  PH  �B    ��   �֙Yf�ac��<魧J���5�z��z��֛�~����=[��c_�իW��<�)�_  PH  �B  s{w��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  A� S���_�(    IEND�B`�               [remap]

importer="texture"
type="StreamTexture"
path="res://.import/UI_tileset.png-9f1d9b8d9fab44b31a2cb0c6f9ce69bd.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/UI/UI_tileset.png"
dest_files=[ "res://.import/UI_tileset.png-9f1d9b8d9fab44b31a2cb0c6f9ce69bd.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
          GDST@   @           9  PNG �PNG

   IHDR   @   @   �iq�   sRGB ���  �IDATx�ݜytTU��?��WK*�=���%�  F����0N��݂:���Q�v��{�[�����E�ӋH���:���B�� YHB*d_*�jyo�(*M�JR!h��S�T��w�߻���ro���� N�\���D�*]��c����z��D�R�[�
5Jg��9E�|JxF׵'�a���Q���BH�~���!����w�A�b
C1�dB�.-�#��ihn�����u��B��1YSB<%�������dA�����C�$+(�����]�BR���Qsu][`
�DV����у�1�G���j�G͕IY! L1�]��� +FS�IY!IP ��|�}��*A��H��R�tQq����D`TW���p\3���M���,�fQ����d��h�m7r�U��f������.��ik�>O�;��xm��'j�u�(o}�����Q�S�-��cBc��d��rI�Ϛ�$I|]�ơ�vJkZ�9>��f����@EuC�~�2�ym�ش��U�\�KAZ4��b�4������;�X婐����@Hg@���o��W�b�x�)����3]j_��V;K����7�u����;o�������;=|��Ŗ}5��0q�$�!?��9�|�5tv�C�sHPTX@t����w�nw��۝�8�=s�p��I}�DZ-̝�ǆ�'�;=����R�PR�ۥu���u��ǻC�sH`��>�p�P ���O3R�������۝�SZ7 �p��o�P!�
��� �l��ހmT�Ƴێ�gA��gm�j����iG���B� ܦ(��cX�}4ۻB��ao��"����� ����G�7���H���æ;,NW?��[��`�r~��w�kl�d4�������YT7�P��5lF�BEc��=<�����?�:]�������G�Μ�{������n�v��%���7�eoݪ��
�QX¬)�JKb����W�[�G ��P$��k�Y:;�����{���a��&�eפ�����O�5,;����yx�b>=fc�* �z��{�fr��7��p���Ôִ�P����t^�]͑�~zs.�3����4��<IG�w�e��e��ih�/ˆ�9�H��f�?����O��.O��;!��]���x�-$E�a1ɜ�u�+7Ȃ�w�md��5���C.��\��X��1?�Nغ/�� ��~��<:k?8��X���!���[���꩓��g��:��E����>��꩓�u��A���	iI4���^v:�^l/;MC��	iI��TM-$�X�;iLH���;iI1�Zm7����P~��G�&g�|BfqV#�M������%��TM��mB�/�)����f����~3m`��������m�Ȉ�Ƽq!cr�pc�8fd���Mۨkl�}P�Л�汻��3p�̤H�>+���1D��i�aۡz�
������Z�Lz|8��.ִQ��v@�1%&���͏�������m���KH�� �p8H�4�9����/*)�aa��g�r�w��F36���(���7�fw����P��&�c����{﹏E7-f�M�).���9��$F�f r �9'1��s2).��G��{���?,�
�G��p�µ�QU�UO�����>��/�g���,�M��5�ʖ�e˃�d����/�M`�=�y=�����f�ӫQU�k'��E�F�+ =΂���
l�&���%%�������F#KY����O7>��;w���l6***B�g)�#W�/�k2�������TJ�'����=!Q@mKYYYdg��$Ib��E�j6�U�,Z�鼌Uvv6YYYԶ��}( ���ߠ#x~�s,X0�����rY��yz�	|r�6l����cN��5ϑ��KBB���5ϡ#xq�7�`=4A�o�xds)�~wO�z�^��m���n�Ds�������e|�0�u��k�ٱ:��RN��w�/!�^�<�ͣ�K1d�F����:�������ˣ����%U�Ą������l{�y����)<�G�y�`}�t��y!��O@� A� Y��sv:K�J��ՎۣQ�܃��T6y�ǯ�Zi
��<�F��1>�	c#�Ǉ��i�L��D�� �u�awe1�e&')�_�Ǝ^V�i߀4�$G�:��r��>h�hݝ������t;)�� &�@zl�Ұր��V6�T�+����0q��L���[t���N&e��Z��ˆ/����(�i啝'i�R�����?:
P].L��S��E�݅�Á�.a6�WjY$F�9P�«����V^7���1Ȓ� �b6�(����0"�k�;�@MC���N�]7 �)Q|s����QfdI���5 ��.f��#1���G���z���>)�N�>�L0T�ۘ5}��Y[�W뿼mj���n���S?�v��ْ|.FE"=�ߑ��q����������p����3�¬8�T�GZ���4ݪ�0�L�Y��jRH��.X�&�v����#�t��7y_#�[�o��V�O����^�����paV�&J�V+V��QY����f+m��(�?/������{�X��:�!:5�G�x���I����HG�%�/�LZ\8/����yLf�Æ>�X�Єǣq���$E������E�Ǣ�����gێ��s�rxO��x孏Q]n���LH����98�i�0==���O$5��o^����>6�a� �*�)?^Ca��yv&���%�5>�n�bŜL:��y�w���/��o�褨A���y,[|=1�VZ�U>,?͑���w��u5d�#�K�b�D�&�:�����l~�S\���[CrTV�$����y��;#�������6�y��3ݸ5��.�V��K���{�,-ւ� k1aB���x���	LL� ����ңl۱������!U��0L�ϴ��O\t$Yi�D�Dm��]|�m���M�3���bT�
�N_����~uiIc��M�DZI���Wgkn����C��!xSv�Pt�F��kڨ��������OKh��L����Z&ip��
ޅ���U�C�[�6��p���;uW8<n'n��nͽQ�
�gԞ�+Z	���{���G�Ĭ� �t�]�p;躆 ��.�ۣ�������^��n�ut�L �W��+ ���hO��^�w�\i� ��:9>3�=��So�2v���U1z��.�^�ߋěN���,���� �f��V�    IEND�B`�           [remap]

importer="texture"
type="StreamTexture"
path="res://.import/icon.png-1ada42475fe106c59fb9885a73678c1a.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/icon.png"
dest_files=[ "res://.import/icon.png-1ada42475fe106c59fb9885a73678c1a.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
               GDST@   @           9  PNG �PNG

   IHDR   @   @   �iq�   sRGB ���  �IDATx�ݜytTU��?��WK*�=���%�  F����0N��݂:���Q�v��{�[�����E�ӋH���:���B�� YHB*d_*�jyo�(*M�JR!h��S�T��w�߻���ro���� N�\���D�*]��c����z��D�R�[�
5Jg��9E�|JxF׵'�a���Q���BH�~���!����w�A�b
C1�dB�.-�#��ihn�����u��B��1YSB<%�������dA�����C�$+(�����]�BR���Qsu][`
�DV����у�1�G���j�G͕IY! L1�]��� +FS�IY!IP ��|�}��*A��H��R�tQq����D`TW���p\3���M���,�fQ����d��h�m7r�U��f������.��ik�>O�;��xm��'j�u�(o}�����Q�S�-��cBc��d��rI�Ϛ�$I|]�ơ�vJkZ�9>��f����@EuC�~�2�ym�ش��U�\�KAZ4��b�4������;�X婐����@Hg@���o��W�b�x�)����3]j_��V;K����7�u����;o�������;=|��Ŗ}5��0q�$�!?��9�|�5tv�C�sHPTX@t����w�nw��۝�8�=s�p��I}�DZ-̝�ǆ�'�;=����R�PR�ۥu���u��ǻC�sH`��>�p�P ���O3R�������۝�SZ7 �p��o�P!�
��� �l��ހmT�Ƴێ�gA��gm�j����iG���B� ܦ(��cX�}4ۻB��ao��"����� ����G�7���H���æ;,NW?��[��`�r~��w�kl�d4�������YT7�P��5lF�BEc��=<�����?�:]�������G�Μ�{������n�v��%���7�eoݪ��
�QX¬)�JKb����W�[�G ��P$��k�Y:;�����{���a��&�eפ�����O�5,;����yx�b>=fc�* �z��{�fr��7��p���Ôִ�P����t^�]͑�~zs.�3����4��<IG�w�e��e��ih�/ˆ�9�H��f�?����O��.O��;!��]���x�-$E�a1ɜ�u�+7Ȃ�w�md��5���C.��\��X��1?�Nغ/�� ��~��<:k?8��X���!���[���꩓��g��:��E����>��꩓�u��A���	iI4���^v:�^l/;MC��	iI��TM-$�X�;iLH���;iI1�Zm7����P~��G�&g�|BfqV#�M������%��TM��mB�/�)����f����~3m`��������m�Ȉ�Ƽq!cr�pc�8fd���Mۨkl�}P�Л�汻��3p�̤H�>+���1D��i�aۡz�
������Z�Lz|8��.ִQ��v@�1%&���͏�������m���KH�� �p8H�4�9����/*)�aa��g�r�w��F36���(���7�fw����P��&�c����{﹏E7-f�M�).���9��$F�f r �9'1��s2).��G��{���?,�
�G��p�µ�QU�UO�����>��/�g���,�M��5�ʖ�e˃�d����/�M`�=�y=�����f�ӫQU�k'��E�F�+ =΂���
l�&���%%�������F#KY����O7>��;w���l6***B�g)�#W�/�k2�������TJ�'����=!Q@mKYYYdg��$Ib��E�j6�U�,Z�鼌Uvv6YYYԶ��}( ���ߠ#x~�s,X0�����rY��yz�	|r�6l����cN��5ϑ��KBB���5ϡ#xq�7�`=4A�o�xds)�~wO�z�^��m���n�Ds�������e|�0�u��k�ٱ:��RN��w�/!�^�<�ͣ�K1d�F����:�������ˣ����%U�Ą������l{�y����)<�G�y�`}�t��y!��O@� A� Y��sv:K�J��ՎۣQ�܃��T6y�ǯ�Zi
��<�F��1>�	c#�Ǉ��i�L��D�� �u�awe1�e&')�_�Ǝ^V�i߀4�$G�:��r��>h�hݝ������t;)�� &�@zl�Ұր��V6�T�+����0q��L���[t���N&e��Z��ˆ/����(�i啝'i�R�����?:
P].L��S��E�݅�Á�.a6�WjY$F�9P�«����V^7���1Ȓ� �b6�(����0"�k�;�@MC���N�]7 �)Q|s����QfdI���5 ��.f��#1���G���z���>)�N�>�L0T�ۘ5}��Y[�W뿼mj���n���S?�v��ْ|.FE"=�ߑ��q����������p����3�¬8�T�GZ���4ݪ�0�L�Y��jRH��.X�&�v����#�t��7y_#�[�o��V�O����^�����paV�&J�V+V��QY����f+m��(�?/������{�X��:�!:5�G�x���I����HG�%�/�LZ\8/����yLf�Æ>�X�Єǣq���$E������E�Ǣ�����gێ��s�rxO��x孏Q]n���LH����98�i�0==���O$5��o^����>6�a� �*�)?^Ca��yv&���%�5>�n�bŜL:��y�w���/��o�褨A���y,[|=1�VZ�U>,?͑���w��u5d�#�K�b�D�&�:�����l~�S\���[CrTV�$����y��;#�������6�y��3ݸ5��.�V��K���{�,-ւ� k1aB���x���	LL� ����ңl۱������!U��0L�ϴ��O\t$Yi�D�Dm��]|�m���M�3���bT�
�N_����~uiIc��M�DZI���Wgkn����C��!xSv�Pt�F��kڨ��������OKh��L����Z&ip��
ޅ���U�C�[�6��p���;uW8<n'n��nͽQ�
�gԞ�+Z	���{���G�Ĭ� �t�]�p;躆 ��.�ۣ�������^��n�ut�L �W��+ ���hO��^�w�\i� ��:9>3�=��So�2v���U1z��.�^�ߋěN���,���� �f��V�    IEND�B`�           [remap]

importer="texture"
type="StreamTexture"
path="res://.import/icon11.png-f267e31b93f4c729cbda1d5f295e0680.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/icon11.png"
dest_files=[ "res://.import/icon11.png-f267e31b93f4c729cbda1d5f295e0680.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
         GDST�   �           �  PNG �PNG

   IHDR   �   �   Z(c]   sRGB ���  �IDATx���oGvǿ�i�C�3�D&EY2���M�^E�6��>�C�=� ȿ���b��!v 	���)'�BK�\Ѱ(Q�Q3�{�������� g����T�W��Տ��s��O�{Xo��t1������.n���&�4�J���3���ϔӿ��i��s��w>�Ṭ�2�o�����U���ny�Pȫ�~������e�?�4�W�Pᨐ�@L�Ue�.nX˛-�򴝗-  Q��F�pT�d^2l* /G�g*3�\軎���6�� ҚI]�5�WY�.C��/�2Qu�L�URXo�z�	�������Lނ2�WY
����Mc��S&Y��'/�$`�{[�A'�����\Z��nGW����&�b1��6Q��[��Bc���^]��=��S���stv��[gOΝN�Ei��8��t"�������
i�j瓡�>l�֯Χ��b<�k'��TX�ͭk#Ɋ�T~ ��գt���\�שק���.�*�
i\K��������S�nq��Ĺ��p�PQ@�<���Z��O�<��K��ϳ�2�*��N����/n"D����k2/ڇ{x�uA0cUNU�h�Ɍ�F@P٤�4���KF���+���F��R�������cE!M1u�d^iTQ�T�#&
�@�����o��00�׬[���q�y��v�o����Ss�o����AQLƎ��vm:�P��
��+�wSm�<�D���� z@k7�]��ǭ��!VU@[��8E}j�ޑ�� ߃x�3��ѡ�N3+�	oE|��J��QU�*�I'Y���q��+�):DclK���T`]�"5y���֯:wuL��'�
O���t#`#Ce�"�2|+@�I��uDj02ԅ�r�lC�D��Z�n���@���5ɵ?`� f�W����؀W�*M�%�����&\(S5�$�A���L��#� b3I�j�<�E���`I�o���P��c�=���`��_5Ə�7�7�}�'��/���D� x���~"͵�ڃdU[��X��I���z �g��j6�k�7�� 0�hJ*����I�V��>57���z� ����ӎ-�L�å�� ��p�$Rf�&�3�vrwv�F�mG����1���Ss��j��Ɛ\�`��~���h� S��$�Wҵ�Q̾��.V�if&{l���k(��(o��1�aG�~�m����P��%��7���AL��/,�%ja헷�s"%f�0˔|g�n�T�p��Gg��Z��^Z�H����lh���__ǭOo�ν�}���Ӓ+ݣe ��+���TC���˒H���r6��8�� �:�� B��>��$�k�!B��C���T�����F�$��a�?�Տ�����#^���-m fi�u��g0��ƫ'��c
�ٕ6�O~ĭO!4���|��\f6�n��~�7���8,��+���G��� E�����?��!��B����G��#D�|C�9����}=*�e6Y@���g ����I6���i����0:��^��Wr[��ڒHD�o�0�?d��W ze�:c"��(4@�A1ՖAe�*&��˗�?���0���QN�(6��B_�X�q�2�`c��p<���U`5�~�㼼g{��ښO�Ɨ)x�ku'uFy@T��� X��r�]a��=z���Yib.�\\�/^|�����P�Y���6 �ԩ?k1s�e.�a\S��G��"�F� �O�G��E��^w�Nu0�h��fP��קc��zo�������>|�y�O
���/
e��9Fh� �h@����<�� �"@��};�}��p8������F�V޾��{U��^��ܣ��l��	�Q�<�����F+2�.���6;�w��w������ܶ��`��4�E����o�4?U�=��`���+a�T������nfj�~|��X��F#���/o�<����	 ���_��?����(t:Ɂ���w��@��^	(�Am�0օ�A�"#n��L�Z�:�����]Y�W�~��ݻx��s ٭ ���";'�}�深���+����d �	�O`k�^���� D�<�/��1�/�;����y`��� �H�A���^=�A·��͛��ll���E���~ ����ԑE��թ`��7�4#�ݬ��~{��ۂo-�&��{%�:@��y��t��PX�⮎^�U�`[������$���({E��{%\!�;�4��Ԅ�?��9M��k��g.]o���y�5���}:h�z�i�M��0M�d�W���D}ʃb���O��W�=��ȋ��p��S�����a;� "^�gf�c$ZUK�**����(�Epn ��I�Ҟtn�s�ە�=�c�17�0���2Py��k��AECڶ�ק3�w]"_?Í����ґ���'�U0���hG���{%L�Y�n��A)�ڻ����e�/����Ѝ�� ���]���s�W��Aj~|���C4���!�=�.�\�t&��@4��y��	t�#���d`0"<�ۣ14S�pI��@�HKG�������[s���){"�I'���=zV+d���p��;`��-� @���l�FDy�K��=�+�-�]���@�g#@ bwL͈�=�]$[�!�Q���^�X���2y%f×l��݋£|޼��fT�Gw���)�� ��S�!3����D�bb:�G�{%\c�n�j�n�8RXR�ļ� 9�HCb2O��B��m�Z��{H{��Kr�(;�<�7��`vz>�,M{2<�ha��Bs�Lb!<�G�Ө�ȵ��3<��J�Bk_ Y�f�����vl�h2��^�+�I��)~�Fi�<��=:{]Q" �9�0���J���8 �/�ӊ�v� �٠"_�Z^�i�XfH��G�Q����M���J��Z=$k~�����!��#����b{B����=�$S�)�@�Vk�"d�^�{l]��)����Xl��$��o�pn ,�Z?�Es��Z�w�d;Nx�þW�*�?Q	�u��P' �p(�K�1�Z^�<<�ܽbufq^*�������Z�r,�XL.�����ylu�� �7�Niױ���4�@�^��&x# ����T~��2(<@��æ}��#��6T���
�J�e<�!y��ino:����w>+_*���<1O�Gw ��|�,��F1��on������� �[▕��]a����{h5�g�Ǉ��:����-N#�IM��2yTtOe˧g/K�%�(���V�'8���U~��<Y3e�[��e�9P�{	E���ȯ��Q�Vs�� H�Pi�O�bkv�:���r�W� �FT���h,j�eH�B^�;�V OԠH-η*�E��o��!Tw��`�=3;��|7��2�˞��*?���?�?���t�yƎ�LQ>�i^�[�����?;텋�{�& ��+��}�����MZ�,k7�ŭ 4ީ�ܫG�)ص���/��cj>�73[/��J�I�ebօ��CY�uܨŅo������i�T���昻0-| =��+��B쨧��N�5(��O���ʇ�3��O6�ݨ�U��|���WO~e@Vk��K�Z�Q�C���z#����!�dy�n�W� LS��>���g��˯��J���n�8h�	c�*5������H���V~%�4�AɌ�T��Cajk@/?�|m��l�q}RjR\�|Qk"3�Vs	�VoD��.n(�>@��)�j!��������/�������4�]$�����D2UC����օ�����H���m���/?u_�2�H��K��w���]C��=�9v�\�wҀɼ�X��6�U�I���|@侤�4i�=��kՇ_0�D!�N�d�(�'?/�(�F�W� L�j.ES-t��0�9��W;�x���W~:t� ��z |�W��i�՚�˷'�Z ���h�EV�*�"��7/_ze�9E�,�ml��T��.��6�x��=��;�k�����(�(�W;�D��v�1�"?��w+?1����|�Μ��ؿ,�_���`�е��!s��Vb�7Y>*;�?| ^�����+��I55�e�U�76��ō�g\o�Q	*p�w��D��?^�[������&�^[��:'�
�>�
_g�g���w+�r�bra�Thl-B��¯�a|��'��by��ɯ��Ld�:�����FE
 $
�-D�.�=�a��y�Ց_)��w�Vv� `X���S�(�>��ҕ%�O;i�uʿ2�'��rM��5�Z�/Pztl��p�����K����Ǔ&_��+a YJ*��1��ti�,񵘨)eﷲt��=i(��廓_�}�ʄߞ��xP�fS��������W6{�x������w�Ҵ�������/�
�-X�y�:� D[�y�����. ��&6]��-Jwf��p{�R���ʹ�Y�������ƭ^��Q��J��4ތʊ(/߼�)��T#(��E2U�����n[�I�������3�F��L"hT����2���Y���c����F�l� '� ��>	:8x)�uK�W�	+CA�dx#������d�H�\+`�Q1��~� �W�f���[�_:���G�*����/_~�\�Q�䥬G��+���.O�W�)���3'�M���@���4�U�ґo��+�w#�� /߼|����n��Dk=@YF��,g߾,�ϟ��G[��P�l�����lr������; ���ž�w/4��K�'H�tL7?������?!zxYx���O5���w���AK`{=A����;���SSy���O�<�ޔ���1&�����?N�U��y���/�(~\��u�d5��fYe ��/O~�s
�g���yV�uܡ����lF��.l��~g��_G��|7�m�2�-��"d>��J�E�y�v����FPt�w�6��9E���WG��%Ey����w�� �K�W�`�.�_�*ODZ���|5�V��'(�/�>�/�ƫ�v�{Xl�ë�6�� ��|PU�|��m��r=��A���o*/߾|���ywh��؂�Z$olM��WK���q��1�A�篥<U����䗲��(���Xl����t����翋�A���<���/ߍ�ҶG�rK z 
�_c�R��y�����ˑ_���j��/*��1���廗_��b��&c�:y)~5�̃���ͱ�_-�� ���\O@���=:�|W0����*xQ�P�ߋOS/��˕_� �0-�^u��@p�:����|�|��-�)J�C.v$�T�BbLPՎ�
���^��˯���Uh	t`�>o���z�#(� �7�nZ�Zej�I�_��y�!�~ O*�E�O���ѡr '({�W�hS)�e�O�)�� 0�!R�hPi �x�Ry �x�a�l2�2j�e�����,'���4����2N�c�UF�  ��	<��Ht�E�q�	F�  �g� �F�)��>��Ϊ�y��� L�I���yF�bQq���{XF2��'���tW�,���g|I5 �St�}�<��X�x|�ԓ�X �������A�Əxd8��l�xD��$3>�yx�n H����Z���<��X@�����k��I�\    IEND�B`�     [remap]

importer="texture"
type="StreamTexture"
path="res://.import/level1_tileset.png-da6487615126c3e3b7471dc277f2a761.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/level1_tileset.png"
dest_files=[ "res://.import/level1_tileset.png-da6487615126c3e3b7471dc277f2a761.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
 GDST`   `           +	  PNG �PNG

   IHDR   `   `   �w8   sRGB ���  �IDATx��]AKcI.%��a�<r�̲ಈ�MO�q��o�8ǹ�-VX��`D���2�����~�%�dF�W�KUwUuwU����� ���+  ��ſ�(˷�ߊb��#�}���Q_P�)aRpem#�� ��}4B)b~���  v󼛄`����{��6{�r���b#���޿����bdtI�V�q��̐�	�KY�+����_����G<P:ϻ��������W23PS��}�ʟg=�k�2��oq�i�LA�����j �w���a#�3�k;�+�\1@v���R-Z��~V���
�6-�B����c�,hV�X?���d{��w����tzo]+poHt�m䗤�N��=c�Z/D�m�G��y��G���@�"6K��ʣ����M��7��g=�ld�6l��͵�d1��c�#]����
�f�>�$�d�>�36�)Ƿ���j �w�YϘNI�/�%�T��VP~ʹ]���9���_�o�K�@�*�nE��C�TFN���(n�
p->y�4'��`L����� lZ)��r���@n�ɭ�~@.���pw��6���meE|$iKQ�r�<e���{9����F>g�hA�,	�ճ$4Nh�o�В�C|�cB�A��q
�'~��Cq�r�Ǭ����݅��V�.;�[N1�!|xS��1t��fv]��TudI�e�܇i�(z]M*�mg�<�Y�R�u�S��Te�fp��]�oժ�,�|(cԃ�
yy�5���T�>�Tד�l3����wK��ބ�\�Fl2�Z�c�ft��}�:��($=V�	����.���/0�~f|��a|��r����^�Td�r1�Pe�)����fI� L�8�~��ǋ!L��6�M�({|��x��~�X�_�N6�pW9/_We+�8�N���2�K��t��
w�AW�	&GVEp����Fh��\��&#P#���
��#�RB�*�~���|%v�(�F�d��N� R��e�j���\���.p6!�f@��&4�T���#�����+�#�K�����g=2P~�����.O��������.�Q�O����tz�#=땂
�����f���'"��*e}�Z�!���7UO����.�Q��|��rC>nJU> ���+_��c�Tc*����+�P�����,��|^�A��
©�-¤|w&ؔ���g��b���p1�YT1��Tg�>ڐ�]��.#p���r�#8;�3W��g7��0���(_�E�;� q�N:��.Gp���
C�3A�|U�Ԡ�ܗ˅�4u& ��")\V��
�!� �j
!i&�Z�V�k�(t?ȅ�8;]lU������>�|������)����Ş� �bD*?$M�U��|�v�a��`9Rc�������8�v���t�#$F@Y.�,[��?������8��>F@Y��������  ��<��Djrpv�7c:5t)�4��S�@
w6��l6{��/�Y����q&p���̈́��Oi�g>���-��6���GPF�(�5�}��R��?`�o��#�I���ݑI�u;X��t�F�u$yFl�|uTE Е��	�=��{��~�>��������rj�DL�fQ����|�	�G���P#����.�]�  6U'j2����h�? �U��N=�$m�\��Q� �㋟L�_�(�6���z��U� �T>�e��uY��}�}Z����?  ��O���k�4�����O]��.�G?Udq�P��j�;5·�?��J�P�������`oi����6k�I]�凜���.ٱO�|��S��\\#}�R|xߵChE��(?E@�nh��Mh�c�ףK����"0�$��}PnɊT�Kɒ������BC��(/��UO��uB��ln��MS:R��\�~ڐ�?@���J
՗J����u��?@�� 	�7�*%l���k��~� V;�F����VC�B���� �ۘ��OŁڟ��F!�y�T�u�7�� i�-U�4������p �<�ɽ���ɟ`{xM�\ޅ6�H�� ���L��O[�}�@Y����|S{�m�w��LصFض�Ӈ?��(�uvA�3���1���#v���+�-����|�~z�����q�kN&���D~�q:�6��0����M�?? ɛ*�d~ �?�,��7l��T������h�n�~�tIӛ��|�M�\�oP�9Bj��     IEND�B`�         [remap]

importer="texture"
type="StreamTexture"
path="res://.import/lvl.png-3b89ab86d69819db1ac9132df0c57077.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/lvl.png"
dest_files=[ "res://.import/lvl.png-3b89ab86d69819db1ac9132df0c57077.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
  GDST�   �           �  PNG �PNG

   IHDR   �   �   ��#   sRGB ���  VIDATx���1n�@�q���"�p������H� �j[
�44tK�4��h�"N�n=Hp�����,�l}k���~]�����4z{ʯ}���c�W�^o`|ʿ�������4:H�R��e���O�9�H�b����m��8���ϩV�Y/_��h��?�V !H�rmd�gڢ��'�	1@B��&}�d�a��8��"}��>���ߠ���Y�� !H�.��	����@B�$�ρn��������K�8����|��/��vt'�E}��Odb�� !H�b�� !��F�<�-�}H������1+�$� 	1@B�$� 	���2���:+�$� 	�|�+�$� 	)���??�>
��DϕE���u��U�͒ǭ@B�$� 	1@B�$$�z���q�fb�� !H�b�� !U�U&��VOwzCc�(��.�n��V !H�R���91�ab�� !x=�����^��%���lC�f�hx�x��c�綂>O���~��?����� !HH�5��+���H�b���9P�Gy��3�ү��'��3�`7�:f��
$� 	1@B�$� 	1@B�z����8�W`:����>�sc���t�O�
$� 	1@B\����D�@B�$�l�l|z?���ҧ�G��]�B�;R��$�>�Ĵ��D�@B�$�ρ�}߃���}տ����y���
$� 	1@B��l�}�ܬ@B�$$�����{��EЧ�|���	1@B�$� 	1@B��&} �����?vV !H�rm�Wq_������X�� !H�.�~�eI    IEND�B`�    [remap]

importer="texture"
type="StreamTexture"
path="res://.import/skull.png-9bdf1057fc7aa45578db5c3824c62be8.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Assets/Sprites/skull.png"
dest_files=[ "res://.import/skull.png-9bdf1057fc7aa45578db5c3824c62be8.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
            GDST3   E             PNG �PNG

   IHDR   3   E   ����   sRGB ���  �IDATh�훽q�0�Ŝv�")��;��2��)=C:��x
�ҁ$ 	
�_��g<B$�q�!�����@�ТA�Q>����^Td�K)K���׿�j�{ߥ"[�MB�JL�|�̙x���'��y��=�{��B�Q�3P���SKQ�lk�Y�9�����e3(1��I+���,��lP��T ����l����1܊�X�ѧ�{Ǥ�fPb\�j�Ŗ��Tf�Ĩm���j+��2%Fd3����� *3U�W����͎<������JL�,v�,[�rP6���0���RЃ���Sק:�2S�x���Jh*X
�#\��@�1_��e�(�b�R�xŤ�i��^�P���6d��n��Ө��ԝ��p��9Eҭ�(1K��*�9ZT?i#��i�LȮ&����}U#7���ƍ�߬�4Ϲ�G3�ָ�ߑX�f��@�㜾y6�M@��f����@1    IEND�B`�    [remap]

importer="texture"
type="StreamTexture"
path="res://.import/Attack-0.png-7482f60561fc200689c4a1bf566fdfb1.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://Attack-0.png"
dest_files=[ "res://.import/Attack-0.png-7482f60561fc200689c4a1bf566fdfb1.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
    [gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "CameraController"
class_name = "CameraController"
library = ExtResource( 1 )
      [gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "Enemy"
class_name = "Enemy"
library = ExtResource( 1 )
            [gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "PlayerController"
class_name = "PlayerController"
library = ExtResource( 1 )
      [gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "Bullet"
class_name = "Bullet"
library = ExtResource( 1 )
          [gd_resource type="Environment" load_steps=2 format=2]

[sub_resource type="ProceduralSky" id=1]

[resource]
background_mode = 2
background_sky = SubResource( 1 )
             GDST              �   PNG �PNG

   IHDR         �x��   sRGB ���    IDATx����n$����X��nh��PɁD˶4	���Q� X,i���k���^@�?,�l���l,,؈6s���h�C*�H�Ǭ&�X�'?������OlvU���SUWyd���~���_�����;�������V�q����r�n��8˺����O|�Y:���k+�+���_��a��3�9���̰s���裏�^�:�7�;�����^�v��o}��(�,�su_@^>��M���v��������K�O}��~����QA8����c�.<�����sܼyk�<����z&c���s��ߗT]Ϩ{�����N+�^�q +��w?"���ҽԦ1	@
��`��#"bo/;����@1	��wL"�[D���zfೇ��{���g�zǬ,����r/`'����r/��z&n޼�w��������<+��-��==eǕ����X�����n>0��$���������g꾀�����z\��{{��s���jC�����;��~���(��]x���/�b�/��Ε�#ɟ'%ì,���ϳ��L�]xr ���{�p)	�T�]S3����1����q��"��څ'{A:)����X��d�qԲ.�E��Ge������|����[�.���)vTYY^)�$$�J��!�MӘ ���	��N{a�|+xT���?�kO�>n0p\ɠ�q*E��$�lo��r���Nݗ �a�' �R�����i���������������̯o����q�ݰVu>9HՃb����x�� �q����]s��^{���G� ����՞ $��4��o|'���ā��j�M\$�zq0`q��͛�*�ELV��x�N+˺�`�f���?j��YI�[6-`^� ���iǭ����߯���%0* �����?��x�������$��|�=_A(��0��];���4���hr`H��?��i����1�4����C��7�U�~�ӎ�������Mie�8S �+��(ݧF�W�;�u�%)�j�[�n����_��NS����)��,L �W.]x/"z�?�,b5����}��IW��x0��8 �6m�=ٽ�a�]x2.�=1���0�����~��(	 ��1���8U~��_�o�������������pp��\�W��iF�/�,�Un޼�+�C�g��>�?��;�͛����#ϗ�獍��� �� ^>���.QH��X���
�ʺ
�$��/�ʷ���7�V��L���[(�/��{����*�\�_5�_ ԭ1�Q��?�{>*�?��o5>�+�
�ɰ>�q[�yeU���Re!��=�b �iD0�5��c{{g`��Q�?=�k�n�@xpx��3+)�[�'�I���͊����M�Ő�hQ[� ��] e~��+��~�࿽�����\�J@��|�P���_DDė��|��g�X�����U%g���t���n �:5:����������qxP���Pq{߲E}�F-�/�W��8�$i����3������rF?@�5*w�޹g���Vk൤�=��5�K<���Z��My���&��ܿ(O��⠿|�/�V��A}�N�+��*����9�w=m��N�5P�0P�F% E{{�@뿬"���i�݈�邋 ������qxpX�D�U�(�e������a3�K	�a�3|'���8D� 7��v�H ��aU�bBP|-����?���N�] �����=<8���*`'���c���S�څ'��؍Qv|�u{�dY7 ����߭\8�W�~�҈ ��DJ��M��1�[��l�ڛ U���@�i�\��?�RDD�u���ޫ��L����l�����_>��T�/������j|��ݏz����� N�> �}{ MҨ  ��ʒ���gF��?,M"���� NWp�^ @�4� II�In��S��(R�"���_b��N����ޑ �kL ?:��i�h�nZ�a�M}"��o���g��i���> @4���T% %�N+��gz�(n����~�xV��Y�o�9j� �GD_�zc�p���̪G{4��1|;�&�a�9�B O#+ )	He�.��i��V���� K��L���<���,7:`r�H ���tZI���
`1A(k���ݻ��>؍��Z�����dغ���˕�꭯����n-���-�����R���1���	�8�-��V�+��wX�?˺�j����Qk4����Vk5���_��e����z�S�{�Á� �[��+A��p*\�zc`P���ma�q�?�)�lo�T�k�jl�$`�z�M���<4	(�T�I�v���)����jc��Xx)"�%4M�o8� TuL��uU���ݯ������� ��?�� i�B>(�S~[��S��RZ�)�ݾ]�D����=��L�������ō��ф&������6�I��:� ��yǩX�ӰPr?oZ�@�'XonnD����ˢ�iG�=�Q�U�i��n�z�K������\����Ϥ�*��w��8J�(�b"0�>���_Z\�(]o����þ*@~;�!��Ӑ���4��] )���e'���>��b@�D������N�EU"�/��w�[]]�%7oފ/=���A�uU�V#,�������?������:�V8�4q@E�����,� ���r�@�j_(b0�_��/���^6����c^|�=\����Jè���{��et����J@��i;ࢲ{=�+�����{G#��A���/y��I���R\K��?��y��?L>	(��e?��p��Ԙ ��<�j� �$�n��Mi�'� �W{�/ş��?kk��u�]	��zf��_5m3WX�)t��}� M2Q�f�߳4���YM��ҿB`-��p;b �T�0L*c�M!,;ߴ�P.�1P�J�F���wѴ���8(ncc�r�@���Ȳ�7�?"�����J��Q�o�[���?������[ ����]6�\i*�Y��Y�w�~}] ��s�)7�ҿ֞�kO,Q��Iv���Yn�U��0/�c ���9����Y�J��$����?��1 ���]U�����Ln1�E\p����[�@�j��Ò��m�SK��ߓ����`X8Q�^�	$ ���4���翨u@^���*������ #���f���&�C�'�h�M Ɲ.x�C�a
���a�4�P�����(��p�������;�0/K�����"+�Y ���S`��L:OD�<�{��K �9 m����;.]z~�:�v\��n�?>"�7J���G�G�@�{ݦY %0��ݫܗ!˺�n�����PR�!P�u��_.���ߛo�y�0�3Gs�o��������Z�'��g��ID�Ӯ�\ݚ�PY���z&�W�v Lϓ/=��� ��}܄��%�i�\:��%-}���E��PO>�kշ�������+[Vwu��V�yu�gW�����Օ�Y ����V�f��/�M1��v�}��(Wl�W������}���fT �] ��qԕ�~���n�~"v�[�} ������/��x� u�0�۷�g���{���Q�tڱ��S��͋���R������rߘ�&��' )����������������J6~@Ep?�̤��
���i��^��x��}O#m	<j=�b%��
�$�?]�Q>�P	Xh�]����� �e��$���=u<O�	���O�1O��e�#	 �vb	�4���z`�����<o��_TOApTccc}�`^�M��4�?˲�������d��i�w �k������Ilo�|�/�W��X�� ��
ԩ�P�@�:eǖ}nXU ��[��:� ]w����HW��d���i1l@��[e�8#������IU�ut:��n��DSi���U(��k�.Ĉ�SЕ�R'>pԢ@��Q�^�1P	�xq}fՀ��	���g+�� �&�H���O��3���d,@J� ��.�V��u���q�������?�Q[�?����0�.<90�a����7���[0̧����җ/�P�z�����_��pY������u|��n<��Q@������� G%���ӟ���E^��/�~���&���OQ"P9@�?�sI f�r��a��~i��a��,�F��G�+����Vk��F�&�|7@�z�����X���� e[�i ��R��T ��;�����XG����n�����^���o��:Ps�ӄ��I��D��4ǿ.U� Ө*����v�k}|����x�	�i��:G��=ߍ�����F)�wj�[���E�K � �:w�����{���'��l���կ\��կ\�=���|w!�q�2A<	%�힉`q5b`R�~��_<��}@��/]z~������Ư~��8�||��?�!���)�ٟ�Z��q����i�|���' ��1	@�Þ�i@�,*&�J��ڎ8���[3߾�?����]x�����͍��w���?��W%���ߍW^y��� �H#�b�x�h�/9�)S�Vkh0��_a�u_T�G&����^�����9to��fݗ��� $)�g���;���IMr�/|�}�������}���j��Þ_}�q��T�� ��ėWZ8��� gI�	@�?w��j�_I gI�	@2���ڍc�*8!K��%y 8)���=yႤ��I ���/��n�b�����/׽�! �Ԙ.�Y�tڥ+ fY7�ן���/���� pF5&�uK՚� P�1	�,��e��/��[�&�;+� �1c f-%׮�X᮪�`���q4"��X?��$`{{'����f�v�FDTo>�t� �4"8I{{Y�Z�h�Z�	���p��{�)"�s�{�?����^��\�e�-�v{� U<n�c��i������ׯ�;�ӕ �\�Q/+�
�U�;6�0?��O�t��ۭ�U �= ������D`�̀>�s��xyk���ݼ�޿;���:Q�_����L ���=,�ϻo�*���"�����O�x �����;o�$�.�3�\D���F�������~.b0ah��������No �,� Â�<f�D�2c���r:��|�k�l��$�G��t:���;��<����iss�~D���ܼ���:�����N��� L�T.Q��?�o?��G�����zNW TN,�q�#�gY���j����X��y)M F�'	�6��t���'9X�$vț6��A�����裟���@QiP5�?�7�4	�ի7���"�䓀Y�78n�?"��u�&"��G?�G3�0 �P�0���Q�?�WW% ��;�Vlo����;n��y�� �qv�3�m{�^�W���=�tZq����J��N��X��|�? �h� ���Q��@�g�II@�K ����qF��>�H�O���w�ҥ�'>./���ڭ?J�  p�*���e��I�����e��5��A���J[���;����؅�V1�߽������xꩵ�������?���5"����+�~��o�Y���C������[.x��v������/b�%?�՟e�h�V��� "��{^�[���{��{�ݪ� ��s��_l��k��*���n�b{{��z�Qu�j�_~�A͖����/|�}�������Qnm=;Ζ��ǹ��lYz��o� N�;��]��Io�[����O�;ǰ����uNZ��. ���x`��[oF�[S�/���Tk��C��я���D<��õ}�����8�f� L��_�Z_`�R���#���6�y�K >y�����_��Eԑ+���2��I,G �X�w~<�Ɏs�׿�����T�� �6����zܛ�D�`��g�}6������3��/Wo�WS�_��qg�7 5� �>}4}v':Ij���Q�-�cч~�	A�8��A_p�O����J�����C��� P��ltZ��jM�>A�UI��{�"������O>����Z�% ��偼���Z��8-��sL�D �I(� ��88pXP��*��L�"p�:ǽ{�R%  �b`@Y0��9;`�ŗb�'�Ol�Y�֫�c  �֗ ���ǥ	������Kq���Г�}�����x���q����vm��4IĽ{�����[��c&� ����=��@��4�Eҗ T������o~3���"A���Wǽ�Ƙ�t�D��&(� �m�;����O2h�nŠ?�$�r� ���] ��������"�����q� ��&�% Y6<0����WK�iI�EN�̢  u�L�Q�|�R=�Fz-�zq����.5����d�ŗzI@�̰�.
I  ��\�QY�؂��ˢ�i���O~����Å���v\�rmछ������,ˢ�iG�u��n��:ԭ�j�,�w�]���"����f�9������X��|�/���_������v�c�"��D`܀�R @��-t�Ww*����7�/\��_f@S��>���J������bD<��W��zpZ�
�,v��Ы �r}Z�?��'i��il��h��u �h�78/˺}��\��{o�*�"�B gI��^��N�������=���Wo�eYdY������>��6?��  �f`;�j��C�t�eY6t��jv7��F&�N{�]�> M����3��j=�| -�-�6yA��.��ӤW��� y䑑���gss#�\�_�ʗ#"r��%;���BN� p��u�z�Q����~�b�~U~J�41�߽������xꩣ��� �p.��~�O������ ��������.jb���h�V^;88��=��e� �p.b�5��������z] ��E����X���1 ���B@�Z��}�j����Y  ,��`�[� �* �I$ �*�>��~���/ jW:`Җ��? ,����� p:�  g�X� ���t�0�$@2 ��  gЉ' e-~U  ��\* > 4�L�,���4 ���& '�U �9�]�t�C� ��K �,;։ʪZ� �L��8
��/_����H�E�Ť�xl�1ݑ� Nֹ����l����E�=���n��ʕk�onn�~>˲�tڑe�h�[Ǯ:  �9q���V���{cssc�VzU�/s���  ��\��7��/+w��� A �W9 ��O�?���2�� ��2�� �^	���zop^�u��+W��5;  h�se/V��OeYdY;��V�{� 89�	@D�`�Q-�,ˆ���܈۷�% P��1 �)���=��_G���? �_n)��M��w<X����+�L���u��"�� �5�}�U���$�� P�s��=z��P�{{Yln�����z h�s��_l�� ��z] �sA ߹�X��" ���\
 8�$  pI                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        7B3�   �IDAT                                                                                                                                                             `A�Kl����    IEND�B`�         [remap]

importer="texture"
type="StreamTexture"
path="res://.import/level1_tileset.png-88b33549c071958c3175ffba487404d2.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://level1_tileset.png"
dest_files=[ "res://.import/level1_tileset.png-88b33549c071958c3175ffba487404d2.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
[gd_resource type="TileSet" load_steps=14 format=2]

[ext_resource path="res://level1_tileset.png" type="Texture" id=1]
[ext_resource path="res://lvl.png" type="Texture" id=2]

[sub_resource type="ConvexPolygonShape2D" id=1]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=2]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=3]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=4]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=5]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=6]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=7]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=8]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=9]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=10]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[sub_resource type="ConvexPolygonShape2D" id=11]
points = PoolVector2Array( 0, 0, 32, 0, 32, 32, 0, 32 )

[resource]
0/name = "level1_tileset.png 0"
0/texture = ExtResource( 1 )
0/tex_offset = Vector2( 0, 0 )
0/modulate = Color( 1, 1, 1, 1 )
0/region = Rect2( 32, 0, 32, 32 )
0/tile_mode = 0
0/occluder_offset = Vector2( 0, 0 )
0/navigation_offset = Vector2( 0, 0 )
0/shape_offset = Vector2( 0, 0 )
0/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
0/shape_one_way = false
0/shape_one_way_margin = 0.0
0/shapes = [  ]
0/z_index = 0
2/name = "level1_tileset.png 2"
2/texture = ExtResource( 1 )
2/tex_offset = Vector2( 0, 0 )
2/modulate = Color( 1, 1, 1, 1 )
2/region = Rect2( 96, 64, 32, 64 )
2/tile_mode = 0
2/occluder_offset = Vector2( 0, 0 )
2/navigation_offset = Vector2( 0, 0 )
2/shape_offset = Vector2( 0, 0 )
2/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
2/shape_one_way = false
2/shape_one_way_margin = 0.0
2/shapes = [  ]
2/z_index = 0
3/name = "level1_tileset.png 3"
3/texture = ExtResource( 1 )
3/tex_offset = Vector2( 0, 0 )
3/modulate = Color( 1, 1, 1, 1 )
3/region = Rect2( 0, 0, 32, 64 )
3/tile_mode = 1
3/autotile/bitmask_mode = 1
3/autotile/bitmask_flags = [ Vector2( 0, 0 ), 448, Vector2( 0, 1 ), 7 ]
3/autotile/icon_coordinate = Vector2( 0, 0 )
3/autotile/tile_size = Vector2( 32, 32 )
3/autotile/spacing = 0
3/autotile/occluder_map = [  ]
3/autotile/navpoly_map = [  ]
3/autotile/priority_map = [  ]
3/autotile/z_index_map = [  ]
3/occluder_offset = Vector2( 0, 0 )
3/navigation_offset = Vector2( 0, 0 )
3/shape_offset = Vector2( 0, 0 )
3/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
3/shape = SubResource( 1 )
3/shape_one_way = false
3/shape_one_way_margin = 1.0
3/shapes = [ {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 1 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 0, 1 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 2 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
3/z_index = 0
4/name = "lvl.png 4"
4/texture = ExtResource( 2 )
4/tex_offset = Vector2( 0, 0 )
4/modulate = Color( 1, 1, 1, 1 )
4/region = Rect2( 0, 0, 96, 96 )
4/tile_mode = 1
4/autotile/bitmask_mode = 1
4/autotile/bitmask_flags = [ Vector2( 0, 0 ), 432, Vector2( 0, 1 ), 438, Vector2( 0, 2 ), 54, Vector2( 1, 0 ), 504, Vector2( 1, 1 ), 511, Vector2( 1, 2 ), 63, Vector2( 2, 0 ), 216, Vector2( 2, 1 ), 219, Vector2( 2, 2 ), 27 ]
4/autotile/icon_coordinate = Vector2( 0, 0 )
4/autotile/tile_size = Vector2( 32, 32 )
4/autotile/spacing = 0
4/autotile/occluder_map = [  ]
4/autotile/navpoly_map = [  ]
4/autotile/priority_map = [  ]
4/autotile/z_index_map = [  ]
4/occluder_offset = Vector2( 0, 0 )
4/navigation_offset = Vector2( 0, 0 )
4/shape_offset = Vector2( 0, 0 )
4/shape_transform = Transform2D( 1, 0, 0, 1, 0, 0 )
4/shape = SubResource( 3 )
4/shape_one_way = false
4/shape_one_way_margin = 1.0
4/shapes = [ {
"autotile_coord": Vector2( 0, 1 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 3 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 0, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 4 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 1, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 5 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 1, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 6 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 2, 0 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 7 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 2, 1 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 8 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 2, 2 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 9 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 1, 2 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 10 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
}, {
"autotile_coord": Vector2( 0, 2 ),
"one_way": false,
"one_way_margin": 1.0,
"shape": SubResource( 11 ),
"shape_transform": Transform2D( 1, 0, 0, 1, 0, 0 )
} ]
4/z_index = 0
               GDST`   `           +	  PNG �PNG

   IHDR   `   `   �w8   sRGB ���  �IDATx��]AKcI.%��a�<r�̲ಈ�MO�q��o�8ǹ�-VX��`D���2�����~�%�dF�W�KUwUuwU����� ���+  ��ſ�(˷�ߊb��#�}���Q_P�)aRpem#�� ��}4B)b~���  v󼛄`����{��6{�r���b#���޿����bdtI�V�q��̐�	�KY�+����_����G<P:ϻ��������W23PS��}�ʟg=�k�2��oq�i�LA�����j �w���a#�3�k;�+�\1@v���R-Z��~V���
�6-�B����c�,hV�X?���d{��w����tzo]+poHt�m䗤�N��=c�Z/D�m�G��y��G���@�"6K��ʣ����M��7��g=�ld�6l��͵�d1��c�#]����
�f�>�$�d�>�36�)Ƿ���j �w�YϘNI�/�%�T��VP~ʹ]���9���_�o�K�@�*�nE��C�TFN���(n�
p->y�4'��`L����� lZ)��r���@n�ɭ�~@.���pw��6���meE|$iKQ�r�<e���{9����F>g�hA�,	�ճ$4Nh�o�В�C|�cB�A��q
�'~��Cq�r�Ǭ����݅��V�.;�[N1�!|xS��1t��fv]��TudI�e�܇i�(z]M*�mg�<�Y�R�u�S��Te�fp��]�oժ�,�|(cԃ�
yy�5���T�>�Tד�l3����wK��ބ�\�Fl2�Z�c�ft��}�:��($=V�	����.���/0�~f|��a|��r����^�Td�r1�Pe�)����fI� L�8�~��ǋ!L��6�M�({|��x��~�X�_�N6�pW9/_We+�8�N���2�K��t��
w�AW�	&GVEp����Fh��\��&#P#���
��#�RB�*�~���|%v�(�F�d��N� R��e�j���\���.p6!�f@��&4�T���#�����+�#�K�����g=2P~�����.O��������.�Q�O����tz�#=땂
�����f���'"��*e}�Z�!���7UO����.�Q��|��rC>nJU> ���+_��c�Tc*����+�P�����,��|^�A��
©�-¤|w&ؔ���g��b���p1�YT1��Tg�>ڐ�]��.#p���r�#8;�3W��g7��0���(_�E�;� q�N:��.Gp���
C�3A�|U�Ԡ�ܗ˅�4u& ��")\V��
�!� �j
!i&�Z�V�k�(t?ȅ�8;]lU������>�|������)����Ş� �bD*?$M�U��|�v�a��`9Rc�������8�v���t�#$F@Y.�,[��?������8��>F@Y��������  ��<��Djrpv�7c:5t)�4��S�@
w6��l6{��/�Y����q&p���̈́��Oi�g>���-��6���GPF�(�5�}��R��?`�o��#�I���ݑI�u;X��t�F�u$yFl�|uTE Е��	�=��{��~�>��������rj�DL�fQ����|�	�G���P#����.�]�  6U'j2����h�? �U��N=�$m�\��Q� �㋟L�_�(�6���z��U� �T>�e��uY��}�}Z����?  ��O���k�4�����O]��.�G?Udq�P��j�;5·�?��J�P�������`oi����6k�I]�凜���.ٱO�|��S��\\#}�R|xߵChE��(?E@�nh��Mh�c�ףK����"0�$��}PnɊT�Kɒ������BC��(/��UO��uB��ln��MS:R��\�~ڐ�?@���J
՗J����u��?@�� 	�7�*%l���k��~� V;�F����VC�B���� �ۘ��OŁڟ��F!�y�T�u�7�� i�-U�4������p �<�ɽ���ɟ`{xM�\ޅ6�H�� ���L��O[�}�@Y����|S{�m�w��LصFض�Ӈ?��(�uvA�3���1���#v���+�-����|�~z�����q�kN&���D~�q:�6��0����M�?? ɛ*�d~ �?�,��7l��T������h�n�~�tIӛ��|�M�\�oP�9Bj��     IEND�B`�         [remap]

importer="texture"
type="StreamTexture"
path="res://.import/lvl.png-0dcc3b71a274691c79d2d8a230667a74.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://lvl.png"
dest_files=[ "res://.import/lvl.png-0dcc3b71a274691c79d2d8a230667a74.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
   [gd_scene load_steps=16 format=2]

[ext_resource path="res://Assets/Sprites/skull.png" type="Texture" id=1]
[ext_resource path="res://scripts.gdnlib" type="GDNativeLibrary" id=2]
[ext_resource path="res://Assets/Sprites/icon.png" type="Texture" id=3]
[ext_resource path="res://Assets/Prefabs/bullet_prefab.tscn" type="PackedScene" id=4]
[ext_resource path="res://Scripts/PlayerController.gdns" type="Script" id=5]
[ext_resource path="res://Attack-0.png" type="Texture" id=6]
[ext_resource path="res://Scripts/Enemy.gdns" type="Script" id=7]
[ext_resource path="res://Assets/Prefabs/TileMaps.tscn" type="PackedScene" id=8]
[ext_resource path="res://CameraController.gdns" type="Script" id=9]

[sub_resource type="CircleShape2D" id=1]
radius = 15.6514

[sub_resource type="CircleShape2D" id=2]
radius = 16.8866

[sub_resource type="NativeScript" id=3]
class_name = "Sword"
library = ExtResource( 2 )

[sub_resource type="CapsuleShape2D" id=4]
radius = 21.1008
height = 53.4026

[sub_resource type="CircleShape2D" id=5]
radius = 17.3234

[sub_resource type="CapsuleShape2D" id=6]
radius = 7.16034
height = 7.08337

[node name="Node2D" type="Node2D"]

[node name="Player1" type="KinematicBody2D" parent="."]
position = Vector2( -175.431, 38.459 )
z_index = 26
collision_mask = 2
script = ExtResource( 5 )
speed = 401.0
bullet_prefab = ExtResource( 4 )

[node name="CollisionShape2D" type="CollisionShape2D" parent="Player1"]
shape = SubResource( 1 )

[node name="Sprite" type="Sprite" parent="Player1/CollisionShape2D"]
scale = Vector2( 0.2, 0.2 )
z_index = 1
texture = ExtResource( 1 )

[node name="Area2D" type="Area2D" parent="Player1"]

[node name="CollisionShape2D" type="CollisionShape2D" parent="Player1/Area2D"]
shape = SubResource( 2 )

[node name="Player2" type="KinematicBody2D" parent="."]
position = Vector2( -70.6213, 42.4418 )
z_index = 26
collision_mask = 2
script = ExtResource( 5 )
speed = 300.0

[node name="CollisionShape2D" type="CollisionShape2D" parent="Player2"]
shape = SubResource( 1 )

[node name="Sprite" type="Sprite" parent="Player2/CollisionShape2D"]
scale = Vector2( 0.2, 0.2 )
z_index = 6
texture = ExtResource( 1 )

[node name="Area2D" type="Area2D" parent="Player2"]
visible = false
z_index = -26
collision_mask = 16
script = SubResource( 3 )

[node name="CollisionShape2D" type="CollisionShape2D" parent="Player2/Area2D"]
position = Vector2( -43.4182, -0.943878 )
rotation = -1.5708
z_index = 4
shape = SubResource( 4 )

[node name="Sprite" type="Sprite" parent="Player2/Area2D/CollisionShape2D"]
position = Vector2( -0.0621338, 7.01221 )
rotation = -1.5708
scale = Vector2( 0.209137, 0.268498 )
z_index = 1
texture = ExtResource( 3 )

[node name="Area2D2" type="Area2D" parent="Player2"]
z_index = 27

[node name="CollisionShape2D" type="CollisionShape2D" parent="Player2/Area2D2"]
shape = SubResource( 5 )

[node name="BulletConteiner" type="Node" parent="."]

[node name="Enemy" type="KinematicBody2D" parent="."]
position = Vector2( -111.943, 96.8002 )
z_index = 25
collision_layer = 4
script = ExtResource( 7 )

[node name="CollisionShape2D" type="CollisionShape2D" parent="Enemy"]
shape = SubResource( 6 )

[node name="Sprite" type="Sprite" parent="Enemy/CollisionShape2D"]
scale = Vector2( 0.3, 0.3 )
texture = ExtResource( 6 )

[node name="Enemy2" type="KinematicBody2D" parent="."]
position = Vector2( 113.557, 78.5777 )
z_index = 25
collision_layer = 4
script = ExtResource( 7 )

[node name="CollisionShape2D" type="CollisionShape2D" parent="Enemy2"]
shape = SubResource( 6 )

[node name="Sprite" type="Sprite" parent="Enemy2/CollisionShape2D"]
scale = Vector2( 0.3, 0.3 )
texture = ExtResource( 6 )

[node name="Camera2D" type="Camera2D" parent="."]
position = Vector2( 0, 15.1453 )
scale = Vector2( 0.439999, 0.439999 )
current = true
zoom = Vector2( 0.6, 0.6 )
script = ExtResource( 9 )

[node name="TileMaps" parent="." instance=ExtResource( 8 )]

[connection signal="body_entered" from="Player1/Area2D" to="Player1" method="_on_Area2D_body_entered"]
[connection signal="body_entered" from="Player2/Area2D" to="Player2/Area2D" method="_on_Area2D_body_entered"]
[connection signal="body_exited" from="Player2/Area2D" to="Player2/Area2D" method="_on_Area2D_body_exited"]
[connection signal="body_entered" from="Player2/Area2D2" to="Player2" method="_on_Area2D_body_entered"]
 [general]

singleton=false
load_once=true
symbol_prefix="godot_"
reloadable=true

[entry]

Windows.64="res://godot_game_STUDIO_project.dll"

[dependencies]

Windows.64=[  ]
     GDST   �           yK  PNG �PNG

   IHDR      �   z��=   sRGB ���    IDATx���y�eW}��������zPOjI4�� z� �l�<"���ya=���@'/$a%q�0&�[���BD�e? F4��cJb@BC[R���꡺���{�~�{�N������mq��n�ݿ����s�=���g������u2A	@AgE��%Cp�e &�0��~��{[�N"vM3>;Nvp^{$r�� g{�,��%bFP	ТE�-F�yJ"N'A�1�@�(� ���s�,�- =ǉ��+��2�E� �0F������N����)^?�%L��	��f��w+� �6Jp����;3�6��|/��D�d��ձ��[�hѢŨC�X3Z;,/�|B"��l�<��<�H��j�W*O�P�o9K��m ^����.`���J�6 9��_���k3�o��g��v��4�3�+�r�_[�[�h��Gb���}Aw	���-��K�%�;���AQ)��`��'�_�뼭�E���5 �+G�G8��� �j�o &����Ĕ@� �gdm�oѢE��Xm
����Q�<"��K�W�����z��6 ;ؼ��s#630R����S�y��9�q��A>M�(�E�-Z���`v �b^�)�|�@|�xH0Cɭ�qi{a$���{����	P��$������~{�ߢE�-�Aof@�f
`Q�m����@-�S�k� >=���������:ٌ�����u�B�t~E �@�@�i��-Z�h
rP���TN�W2��J�F]�z�j���6�.�2Śq��/����ī@\���k.lѢE�-6
�]���"�9O��'fWT0F�f|�+�5zp�2�?^Y�& ���:d/^��w��(�E�-Z�,%E�v��{�o�pj`Q-�Kʁ�g�|Z`h�[����1�m `�	�'cdop� �l��[�hѢ��AﺴbA��˔
�+��� Sn�ҐnJ������ �k��W������E�-Z���XyF"�
V�G�j��)n��Ƴk�"�_���@U��S�2�7�&�+�[�hѢ�Y�^�M���i�BW�a�v6�F���0�uOm�x�Gr��n�h��oѢE���@���#��T�A��̛n9�V��f�����������W�b�w3��f�[K�b�-Z�h��������xI��C��p�Z�O(w�}�7'�#ypw���o��rD�	�v��2�Kb\���oѢE�-���?�n�D~��w���?�)���yS��F��/��&�r��ٞ��}-Z�h��G+O<X ?����t|&�Ł����{�ܽ�	��;�q� �n��[�hѢE��l@9/�w o�6 ��߳�#��"�w��O(�N����FF~�@�ſE�-Z��CR"�� �\���5�.j7 7��R}*Mp�V�>��y��l��oѢE�-����t^����N ����PkoJp�@�S ��Nd�!>��G��B�?O��?c첒�Z��hѢE�?
��d��E���Z�҂�Oո00���{������0N�����iѢE�-��ѡ���凁?��������Q�����_�M��>�.��ȳ������l��*.W�Ҟ�hѢE�� ���ʃ�����?; ȑ��? �RW�r
n��	��&�SP�S��Q (��H�o�#~�w��h�j�/��n���&xѹ��d�����r6M�LM��i*'�<7�S�u>݄��og�k�TWC���8L�6����>�|Mv���P��{�r����WW�Bb�"���R�C��6�o>|>~�y������˜�/8s���\���f�3�a���_�W��^c0J́�@�����%�	ࣺ���e}7�P}j�2���������Qz�_�d�^83�3{qΎ\�s+�\��=��صg��_"W�;��������d�������~�6P�Pl|��PlS����Ѽ*��n|�����V��=���h�ѥ(�Mp��T~�c�i8t��=�#�����9rd��GN-H����
�O|z������g�|2�T@������Ž��s�/r:/�s�X��@�{��];��nf���{�fv��u�Ry�mc_Y*���b�)�}l�P�w�u|����φ����s�Z�C}�*�Mu��9Uu�W	G�]`�ߜ����<��I�k�g�,�#�V �CA��K�|J=��5	�[��\��^�_�?X�F��n��_���_�L3�ˮ��ʟ�e��Y.�`+S���"N����d���4�q�ll���:�T2Wζ�L�6�@���t!�DBfl��r��r��'%t�����[����)�AӶ�әr�Wu>�h�M%��W�&?��/��p�X��O���9���s|��9�Yfr�ޅ���,� |�'���+uƭ�ދ�ky~�/1�x��	�S�ߡs�F	���C�[o���_��sf�8g�d�J�A�w���c|�=s�2����M�R���6�?j���L}�_�&��Iy��<�����3��]๹�|�[G����R��|C��]� Wv�����[�\�帚ϲ�i S��u�t�A�/���7��g�|fg&�ܔ�L�x��ޛd�(���ߔ���.��צ�}S�{�P�ſ�����D���M�4���8|g$,�)�;��_��S�ŝ�(7�d_�����s���q�j>`j>�!�e���KI`�8ox���s�ضm�=m�EokF�1����U7F�<�O*}�]�}�<M!�����c�D�߈� �ב553��#�4A��;����~���A�(c#n+�\�R�gེ�8��f��,3�8��4;��� ~M�m�^i��	r������^�5מǦM��#����?��0�Bd1�M�|���1�M�¨~�Q��7�R��v�P�}9����;��O��e?����E����C�dy/(�Wj��ϟX9��{���,��+M��O�����aN��H����,�߰������=a;��G��ŷɂ>�����c����jRs� �>o#��cc��R�P��͐o��O�����#����'��Î���-����+�$�ȋΰ�$�P��\���k>ad0f�N�f���9��.!�>�!���H����w���W�������=IF�`��]c�)��f�~ ��.nH,�K�o���٪0�G#��T�-�m�t��8\9�`[�P�9�6D.��x�1t۱��f�ڑW?ku;��Q��lˣ�q��jl���$���b�֥ʥ���b�ƺ�6{[�.~SL���O��o=�?y�e����y�{�`Uw!�X��S�[�Y^ϗ��O���-�[���"���"%��N��B~��v1�)�_�rd��Q|̑x���:G�Mr������R�cmc��v4q��k[G��׵MuD˕�'��I{����♂��ׇ����q�=��D���� dQ � �'����~����s�Y���e�uM@�ljS�����]������w�b�����kZ����7i3,Y��F�BlB�R��"����إ.�1�a�:��l�r�>�[�p��)��G��N�NA��<���Y[���&��t��+M�W3:W�~���{_��s���y���*�*�uƣr�6���3>z_�:��>���=`3�G���&��6p6���m����~�o~���=V�����S�?����5>�.|)7�\��n�+������a�w����37����_�X}d� �Z蛞�-h���1�::��M�]jߍ�p}���݇�.רM�Ǭ�Q:���J �W�f7]���Y�l�	��f�o�r��y�Q�c��-kdk�wp'���k�,#|��g��F��^�߾{�_z�>~��/$���0���<bo���7�kӄlr��G�kc��w��t��mſI��ez?�g��ۥ���
�������x��y��ƛ��/�+Nҽ8�#��~�+x7���{��O������m���ɖmc���y�+����c{����׍EE��>&|���c��|e:NS�P�+����&���7������V�l�ɇ���xM��Ke�N�.�N����b�?T�Ʃ�P�\5�/���6��^��[ջ�cm%t����LNv��'c��r�WH$Νe��ۺ�_�]�x;w��fV�G�����l�{�����\�կ9��x��5����tܺ�ČS��r�)����d�z��MCꯪ�>+t�^�F-V�{�nj\r�̕�K�[�cfM|��C�u�َ�u�ۖK�#{�ޗWB����3���1c�Td�@nY�8|z׃��
���S����yx�:A���s�8�2��ŋ����eE��ƩlS���K��[�R6)��y��>�.�61GPu�]ܾ|!���G�6y�E�#���������8B�]�}��+��������%���o��㇗��ge�ʤ|zHJٞy�,YfVf ��fsG��
��6N~�@L7�w��~���{7�ڋXs��oa)��<ux���)�:\!|��>�&�����{<_{�]���0�>2_��a��<2o�;�����Fq�����Cs��]��E�e������� � ���J�����3�r�8�P�����]��^�(��#ő{�"��~hգ��l6¶��G�kS�~��D�-�)���1|)
{!E�e?ېF 4F/}�v��8ͣ��j��������t��dY١��_�|�|
��S䯗��H��^��_���V��Oq����h�֤L7�.��cS�PNu�L7��+��4�L�6{��K磯ڹlbxG	�\m������Wyu۠I��E����q�2ݺ)-2��.�n�F��
�H1�-��;*�Ne���cy��,��/\�ѹE����=1P�E��OS� ܮ��o�n@�����䌽����.�ݻ&��s����ҭ]
��P�a𤊙�����x ��������l������ۈWl����d��}u&^����W�jF}�Lv��>6u�mp-OH��;��j�(��p�0=5ƶm�<��	N�w�=0cl2G�1����V�<��s3���uYf|F"iM$����~W�����}
���>V����%e�:�>�P�1�)K)�ч�,��XS�cPg��j��cO!�Y�i�aO�n�ڨ)~_;;�O�O�|��'�i�E����|P��_@�X�i}'�a��77u������?�b�ƅ�^����T<�*�)�&Ʃ�Ț��bbה(��|��j0�(�u�c�zOݸM5M�v_;	"����rp�O��Lc��eE����Ґ+��3 ��������L{���-c�|�e�:w�u=�T��rݸ���.�!G詏�8�O�(��R���z_����]���K���[�Cy���s��ҏR#�t3�4�I���)��w���X��}�T >,��f���N �i��(y���r�e��o��)�R36q���r���چ��ch���i���"���խ?_��W]W�ər��\���&{_��+�����a�'�>$��<Cr�I�a�Sgׅ�/���o�˩����; ΁�:U�u{9 ��[ ;뗠>
$�1�[�٧��?v��� �����r��ŶS�q��\��2��b��4�3��2��2�]��Y*r��N�[�&y�/�W���X���.B���5����+�W�K�.���_��:>]\�����}t���������u�6.�{���s�w���%D7@�r�>�c�"�wM��D�֠����@�$� �B�521G��￈��\����W�tu�L^̆�ˡ�X7�:s�\; �K��-���ځR��.�./��*����\*r�z�-t�86�Q{�[�:�������#�5�&���ʧ�s-�n�l��j��5��M�x\vU.�������G;�rN�������[�� ����Ȗ+�)?$a����e$/����˷�V����.���7�#ttنl�!��wG�c�W����:Yʗn9Mv!�M�j�S����&r6�T�*3����xB��Ʈcm]y��0��褧��.�·C]�����df��=) �H�]���@����������y#���������1���f�1�l�����s��eX_����6ֽt6>�B|}�\]�᳜�<6��W�ub[�1r�,�ׇ+45���)^��-.���R7�:!y��:�OM����ǙFf$�LN��������)��K y��%�����-뮂\��ұ���RoX�_��csq���a��]|��-?�L��٘|M|�X�\��.C�}S�&�Y�6^��d�,:_Uf��Wa�G���g�ؚ�ږ����铫��/�o�:]H~x�y[x�O�`��&@ �����$���Į�KT7d�?�y�.�l��o����}ul�ؚ��u:�ݰ7�&mC�t������ƇG���M2����W'^ӯa/O���$S���F�����c�U�V���g��.Fg�Q���Br�|v[6O���"#�.v$ vu�޲R���C��3Ķ���$��d3{wn���P�����C��K�1���|��c���u=л�L|��o���q�ϔ�K��oӅ��|�Y����>����M>U��ǥ����O;[��q��h��e�06��}�.�~۲T�'!:�x.��yTu&;����t&>�6%�����%/���L�p �$Cl��d�B��l�(Aɕ/�̹���_�f�Y��c�b�m|�v��b�����+�I���J7V�M��!3��ҿ��)g�\�u������t�
������:�1�~.�*3�	�[f��ec���Xw����ƥ��>g_�::[�P��<|���Rp��l�%��k�+_�Y���4�=�m���*���g��S���V�ٷs+��p�����˗�Cw������H���6$wn��k�	�����]~!!/Rr���p��&�X��/f�e��T�!��q�� ې��r�rt�B��V�!|�|\�o�V�2��J��,��g�^�����@�X&W ��u���E��n�f�^��J��c�g#6�u��!�!;<W��%s�h��^6�X���5�u��Ue(2u컍���0���Q�Sy}lC��ѥ�p-������ZO>>�Ε�ɦ��_t�nS�IJ��9�+r2:�s�����|�!�}�nff{��_Y>6�P�O��Q�N�K�K����>�&d1r_���0�����1�/6���!2�:ԝ������c__����v�m]j�s����p�y��c:�o��ǜ��a߹��k���S�t����ID�d�۽u��8*�
y�B9��:�-x�.�ub�|Sګ;��I���GWǶ	�~_S��)�6[�L�x���[�6M4&�:<�Ƿ�-����[�C�m�%�����b�|Kط{+�<C�\�NAv@�!_x9;��>�/��=�_�e�ջ�R�CyG-f����ҥ���ه6(&Y�m]��{"[<����TtClmGa&y�W���]0��|}u!3�Y��`�rF��Ђn���S��;��QmJx��[��#�?����8��� G.̶0�W"���s�Hvm�Ķ��[��mc��n�������2����NŨײ�ƪ.�K�7�}8T���$������!��9��L2U��L6u>s�����Kǣ��ѥ�Pm|��e���Z�M�t��Tey	�vN�k�&J#i,$�o3{�I����/ \Br�����wS+3�+��1�nء1M|�;$ߜ������rq���ll2��d����
�]S���e���������&9t���.��.��罯.�'�&�˔� ��x;KF�8HJ2��'�vt636��S$n )������L���nD�x64�A�����O�W����n����������A�O̹}��w��|�\Zƪ�u~^g����@��yx�#�\�I������n�����r�\FS��K/��"�3��=9���dd{��=,"9���O4U�c���6Ո��u�B}R7�����k"��}�u�0��ۘB���CƮ���Y��s�:����kVRr�	�[x}u1��\��y���,6�e�@F��#`_꽉r2v�;g�    IDAT\���%-fMi[�Q-�)��0*[�^�1�l�/򺝧n����}�M�KWM���֏Pdy����]ul��?�x����&�Țb��\v�BUS�}߫qR6:��>�����hB	;wN�� ��["`_'�~ H��)���Cv�� ��aֳ��oD�qCt�<..ݝ/:��jj�]�t? �C�P��7�M� ����gߠ�Q��..S��٩������άAS26�T�4��:����}�����-�$�]��ل�@�	�^����O�V�u�mvM�x6�T��Ei���.��U�}�-����^�"��}�)^�9�.{�zuٛt�:�����B�c߻�B���k󭓋O<W���w��ɟا��@Φ�@ؾ{�;�<fCJ/4FLn<A���Q�v��;N��w����6E��lr��oH�)�S�����NT�~�b�!�C��������;�&&�T1j�۾{|�Dz
�j���D� 	�̌����!�Bb�����2�T_V��M�2�W*][�q��&����g�\�tn]'s��>�S�!��:�]���u߻t:�.e.>�Cs��o:_���>ffƒ}���َ��"1}�dj��*�OU�b�y�<�]�<Bmlvu�y]���)�h�1��c�Pw�6;�^'�)�j�:��Clc�cu�ئ�U�TQv�crO�G�Ƭ[*�S3����0�����;�M�1�1��:H�<�xSŶ��?��Vlcb��[]�����+�j��ښ.(�{����v���ؖ����ƴ�l<���Ah������b��)Z�����&����Ę��4�� �v̤�|� _ɔ��MyR���𱏉�*�x�(�1�Ms�ݪ�����%��B?;��D��O��F�����t)o�"W������N�GR6E��H%��Ы��o��� �#� �db"o� ��S��E���W�R54�<B�bl���}u��g��Pm}mLv)^&ޘ<mˮ��љ����RnS���W��-n�eͣ.B���<&&rR_��G���o)WJӨ�S�����ub��N��_7ǔ�!�6�<�#u��M���U]�#~�8$�����cH�M�N���md�&���cɏ��`#��T�YLAI���0� B|}�w������Sߛb�66��˗Wgg[����}u�����%�a�s��O�����š�MԀ���|k�� ^	Qبu����sa���G㟪�i2����=���d�[�}[��Z�S*�ݰ���|��O�7�y�և��N� t��pg��C�>6u�kJ4���)����qLq4�4�a���ʪ�TS�jn1��!�><uQ'oy�ͰQgy��a��[��c��1%V>*H�<u��N��T��:�#��$��eBS�e�݉�mqV�m Z����Ȕ�[hMrSqW}�XØ�1���]�h�mТE�-Z��m Z��0�K�s��	����]y��EEfz�"�O�M���]�h�mp6#tG�;�H�<u�3�ߧ8�`�{��ב��n���2��ϲ�����8+0ZwT�*Neo�	�5<r���ާ�O<�<|�C��c�U�(:�?�:�oC��a���DS38�6����0sݏ��3 #�Ҁz��4i�y�((����)w�MųY�u���u6��{������	���#佉ǆ�����]�>�G�4��ZF �6 M|�1G��g��4Q$�]�cbԍW�0����|
�:v�C� ^��mY����ձ��������0��9����F��}q�o5 %o*��) ��kz�	ߍ�]'��\��Mr_.���\����b�A��Dc��䱨�s�)�!��?���-�M4(��1�淑���F~�}d��;��b�\'�#O�[�a��cTwj��#�8��.�C���1٥x�xc�-���Gg��b�K�M��c�[>\u�ﶸ��54��ͻ�o��X\,ͬ�2�p*��΀��Eo����Ǡ�/P�<|�c���7^̎5�mgZ@L�Ez_[�Sm�~����ٙ�
��4��[��|�WU�z_�8t�c����0��O�:y�`�ǩ����E��Nu�9�)g�{@Ws4��}�7�S�<|���S�u��/���Z������*G&>���G�W��-�.�Kn�����tE��ک6>��-�!�1�R�̳n�._�a�:y�|��&���n������8���eN��4 ���
��h��R�a[�Ty����>
M ���W�,��L��b����:��&W�1B���a���S�ږه�ɆaM���ZDcb7Q̛j�B��ӧ�dɻ�@��H�\zj8uj٬Lu���`��M�<�݌4����`�S|C�Bt����i��Qe6�j����U����nD�[lSp�,�&�.e.���F�y�"�I8uj9y��ȹ�9�Hx�9p��%?��ZH�������YW�������?Ѕ�bW�Pc�t!G����Ƨ�1�lrS��p��it��� ��)�!<����H꘡�����a��5�}v������
�\G�\bnr�?<�~%�غE���!e)���M ��]��|��T���&��>�:��M�O�a7:Y�q*ۺE8�?��>�6�:��l*��#"��ϓ7��0�)�P���~NCA�b�>HXQo�X�,�u�5���̳�O"��h��$�lU~���+���T9�����8�j��ȥo�u�jTLM��1R?/��۱���}�&���85wJ��xX�?U�*����/`?����@	�2	�����
J^���%�� ���|�o��eg�9��i����������r��ݾ�����2�]UV��ɫ��e�u/��vۢMoZ>�^�~t˯�Mqu9b��ݖ]�T�}��J�ѕSU�Z_n�O].�?U�1�����U������.�H؟��ғ�����۠L�VvoSp�/p�:N�]w�����xB��K��ŷ��^.�.5/_���Yg��K7��Q�!cW|���Gǫ��r��a�>Rp��B��	^���.�7r?��<Q_`;PR�N�<WR$0A�Ï�81+6�ƣ������kC������p���B8|xbmU{��Gg*We!z�8M���^w��lt<���ǥs�`��b9t�ct��}}bb���㻜)��e#��G�3�������,�u(���Oed�˄OG���GA^�7��S���Ʊ\&ސM:��jL}|�tܱ��9b�tq�����|t66��k���ƉA��֦7�cd16uƩ|��Q�h��7]�m6�\�����GO�%��()�Z�<�����ܟnO�C����3;��������c���^�ŗ��?eL�����Q�I��[�XՅr�����*�q�d�:�>�6�2�P�I��U�ɦ�gn���5q�xt�>���ϲ��\qc�]붩�.^6��l ����E=��C����ԁ�D�H�, ,����\�k�ڟ�?���7٨v)|�6Ԍ���7����9����`k�&Ct�G��-d��ٛ��}�d&��m�NE�m�g���q��U���;g���}��3�����K�]�叉i�O��d��GO�xP6R�K���Υ���|.q�D��g�sU�˯X��h�M�-�Nn�i�v�T���v��bl]ˆ���k���׍�����%���&A�)�����eR�Mr_��old���.�!����]�'�7���g��N_rI�ܥ�Cg��'���P��9ɩ�]ff;��L����1�������V��Rp������'�n���<>2�ܕ�OQ�¯�n#��mB|,O�&��5�b��_]j����؈����.��94��I�r +()(�-�?��6�<��3<����^PE�N)��O����M"?��7G�]���л��d�m2��f�{�����t��E��}���q�\9�t*��mh~>���e���\���Gչ�1�d����ѯ�I�@A�D����vA�R�?W"���e�q���8Œt/�0V����f��nة9R���ՍM>���&T�kk�w��p��LH��cá���ce:��1���SՇؚơ:lCr��a�ѥ�/�[���Yx�%����9�R?,(�O��&�0IgI±���Ap�wN�̡��OHC3N�����c�c���>�����L~&��Iw�X�7��̔��q�'թ9�<�O��z�����'c������岳�0q���Ƥ����L�	�,��fzj$���n)��K��}ξ�ut�x�!y���٥�6���3x��<��dS���pl���$:��Y�3��M&<�#x���8p�$�;�[ؐs�u�{ަ�9�P;)��jk��G�W?/�}����hۦ��U?�z��lr��N�5٘|��`RA��)|l�<&���$���\��sgOL���ӷ 7ec�4G��s��=x_���'y�������c���,�R�}	��{��|�k�8qrquN��l_ݗ1�;Tg�3�]9��|tM؆r��U]���ƇG���M2����W'^ӯa/O���$S���F�����c�U�V���g��.Fg�Q���Br�|v'N.����l��� u)�4������Jļ}m�a������x���h,dC�b��9dC	��5N�sQmM�.>�ؖ�I�{�lL�&>[,[��|�!־�WyǬG�Nn��Y��*3�����٣yo㳍ClMqm��zo�����Η�7G�.$�$<��	���Go�=��H2�12��((�))N�_���D�m����z+}�.n(G�cr	�Yg��7��ƺ���'V���ܖ�k9|�ӕ�F�B�Nl�<F��p�Ƣ�^76����%��wY��R�#$]\��������lj����
�{� [���R� 0����������{�xٹ8|�c�����o������c���W��L��/�r��B8��9�r���]�M�l��rUf����Ƶ�]9�ں���a��	O;]��� :p��G���9����@����l���`0��D>�Q���Ŭ�Y2n��c���;���W�E{�"Ǣ�c���pu8l.���'�!4j��������W�S�4q��@��KX�T�`\�S��WsG�S�[�*�
5��vԠ�}�_u=��u�)U���M����@���R��n��llc�./[!��I7v��l�E�3G]���\�-z�ن��R��u~p��ap@.�?�m���#x��|�+�Ym=�w���4����crQ_��*���e����ơ��i�g�_�Ce��Qe:;ۭ`���[�L���n�˔W�nY}n�3mWuW���G�@]�X1�j^�[@��_��:>�-�:Y��`]��x>1}l�z������d��\�]1|s	�Ё/}e?Os:�����]���A�������|.#ۓ�v�f�����Kwp�Э��[�T;�Ngg������=4��<U{�8�Ç'Df��k[�����b`������}�0�}�\6&}��������������qcm�4uuձ*�������`�������s��nMĕ9 �G2r�6	2GO,�ů?��|���v���=ay�K�ɹ�ck[�P[��I�w��^.^�w��-������'�����䣓�����r�]6�{<�cmM�T��:c_�+^,̗|��q��r?�;�#���*��ܽN�s]��	a��z����}d9k�Ϯ5�����+OHn)��C�S��,��G��K��C�}V�����cҧ�o��5v٤�[,Cs��J3US��	(������'@[�S@ �(��f�r������p{�=C�&���;>�4���y
5p��{��3٥�	�8Sp�|}�}�}�����L\���)W��W,5|S���2��hҙ�B�ue>���|�u��,4����וKWʘ!<��ձ�~p�;>�4E#��!����u]E��Ȼ�����p��E �6q-@��C|���ٽs��;��G�B�^��\�ζi��`��V�{��%��!���*�k,Y{���WK�鮶�����i����t�^���ڹll�x�m$br�Y'.^��7'ur���/&���&3�lȖ�m��16�w�ǐX�l��������_���CL4z�����U�$��Fk��%�+� � ��<����c����|:��<Mت9���;V�Q�1W��ƺ+�M˪�t|&���tq�|\:��S��Ψ�b��e��,C~�)�c�Pe�;L2��.�n����U�r����!ܩlU��c,O\�?�����7O4V�{�:H�X� �|�7(�����W�|X4����u�[oy&V[�>v�<��!�������Sq��^:�����%�����.kJ�����:p��Τ��xtr�m̲������эM��9�ᶍm�x�}y��	���G���C�����t���*5���i���-�o���5�ho:�;��iS�n����N�W�m���)��>�Ǘ7�+����M���W.��Ce�\B�&~?�o��O�:=��D1ܾ�.;�>F"oZ�K�8G�񰸚ȩ���O<�mw�g{#��[���߮���	T/74��>1��#G�B���Hlg���oغs�׿�|�1%q�SW�}lU���'�/�o�������/����Wf��P��� !�?�A-�u�S�b��y�>�Ї�������G��"��n.����˒{������4^���`�v�O�[o[�;�S�$���3�h�� }Hf��q�{.�կ�Cg<c]ϡ.�mlz���4�6��c����o����q��+�q���]�����7�M��y�@�U�/���L�v�X¢���4I&���֕�M��1���}�B�gu<�͗?��'�a~��K%���|��1wl�����AQ��o[�@roZ[��;�R}�la�'2��M�0@��ıe��ӏ�����W_@gL��9��ձ��Л8b�k_�3�*�룳�v*��S厕�8UY��
�N��M��n�1!fv@����W<`[O���p�Bu���"7Ů#�=Tͧا�	��ɭ���ߖ_,��)�.K���S|�ϟ�ıe:I{W��g�X��@6e�����&��UL������q��E2AΛn8��q�� �9=:N�]������W��+����G�kb��w#1�F���e��t)䱲&�bfR4
u�S�Cm%|�G���gX�h��/S���U���Z�Z��������}5�su�� ��P"Y^��s���yYo�Bw	�����o�#��I��?�;F����c�3��ٳ�F �ܤ���O�,�����B�"��?�.���s�Ac��]�CI��e���S��{5  ������?����.�Bg(��-��߸��{g���m��}̸I�a�Bm7Bbb��wq6�K7��^G6��Þ����%8p���чx�l����i``�_��M��x�:?�E}��n`m�/���0-���F!��[௿�[�tصc�wq������P�����g�����]Wf��kk��������2q��8�^u�/d��lmz�����m]�+����'�c��>�d��P���,��G�o��Z��%$��a	�H�CF�d���~�|�Oj=�x'w�'T��/d��2��M^���d���y��~���>o�wJ ��xU6���t��]c�)��f�~ ��.nH,�K�o���٪0�G#��T�-�m�t��8\9�`[�P�9Ǟ�p����ێm>6{�κ�Y�ہ.��7�`[��kWc��m�&���ö.U.���K7�ŵ��rw�b� ��}�4�}�)��Ƀ,�|� A���	��x��;�- |�7|-x��8���w2��ӌ('Q��gh%�%��~j3��j/�~�^�	�J������^�}�S�)�S���}�!v�E0e߼ѧ
R��B�|�}9]v���O����%��m�M
NWc�ҫȡX���������_�d��� #����<K�?�����/d���Fg�W��5㝽SL2���=Av�0��b��Mtx�u[��/�Kg{�>i�.�)
�0�0�Bd1�M�|���1�M�B�}^M��mh��f��]�=,�uPE�{=����}��;Np�.�>�W��y����,}�0�kl��T�J��Kʏw�~����HX�w��r�r�  IDATo��[n۶M���t6٨����U�S�&�{ʙ�:�M�4�Qo�4.}�b*O�s�`#����^±c|���/d��1t?��4 ������,��m�5 ��@��JN��a� ��)P��o��������L2�)�-]����:G�B�m]�y]
��M��86)��qZ`�3u�}�m����댛��=ڗ�p�`����O�w ��E~�!�((�Z"�YMt}P� �%�h������+��| �@���ް���r��Nq����g����Hɓ2����M�R���6�?j���L9՟�f#��Py�#�X�T945�����?wt���N�o���K���z��w�> �J�]7��j�g�����������_� ��n��_��M ����L3�ˮ��ʟ�e��Y.�`+S���F �z��Lҟ�1�u&o(��+�̕�-'��M>���6]�4����M��f�鲵�`#�0M@�l�����j��\E@����oҙr�Wu>�h�M%��W�&?��/�+�����ǟ<΁�s������}s̳��P/�3�١��A�����d��&�V˅U-ϻ���gA��qĿ��h�� �m˔vo��k������ݶ�}/�̎ݓ+�;k^6B��W����F٧<��sD_w6�i�:>�G��US����9��R���LASG�ur�ꪯ�<����9Ɂc'y�<t�<ϞY$G26�zſ���%�?�)>�� ��p˟���n�A����?0(��{ct�QF~�0ota�X���d���9;vLp�έ\r�V��bמMdS�ƚ��R���mG�.��_�l}��M�͘�@7��
�3!ūr�f�l~�Y*��
u{-�>G㱺Qht�a7����p��>{�G=�㇏s��"s��Z((�C{|�/zG����t�MI��r��f�|�7�F-Ỹs�}�� �c�ٞ��0Є��^f�.��ޜ�&�w�4{/�bf�æ��M�9S�cl���3��[�}lb�B}}v�����doC��~}(b��<�֌B���X��9�9��ѫ��M���R�C��6y�)�:|u��+(Jə���93_p�t���.9��g�9�"���v�� �2)0J���wp	���G�~ݭ6�V~��֟vAS�>�[�(]��#4���
r`��Q�N,��3�y��cHz3����[�hѢ��w*_TN��
{���o����B ȑ��? ��
2
Jr
�u3a����{�uş�������vF�Q�&�E�-Z�8[��u�'�(?,��X9��;�	�L��� �����/��%���|�Ky"�K3�v���-Z�h�b�1FI��E�-�?E!V,�\��!�=rS&@)�+�Jy�&:��C��ۙ�-Z�h��}�����A|V��_�1����<� ɩ�w���)� ,"/���g2�W�����-Z�h�b��%�%�7��|��q`��&�S���ې��>��m��q઒�v��i¶hѢE�g=zW�����v�*��E��ʕ�e��� �O�FS��C��@~@R\�F�E�-Z��Q�X�ͯ@~ x{�~N]�����'��gT����݆�� �(�� ����o/lѢE�?J��/���/R��8�]�zT~�r��D�T�q�����o�Mʑ��p�!N�\R���<��ߌТE�-Z�U�ȑ��K�?9�ɛ����Q{8��L^���9���w(ş�`�,����~����[�hѢ������L���c�C����� �������-5����ѫ�n�������1����rݽ�-Z�hѢ�ٍA]�H
� � [��jcu&�����kxwk��6�Wޏ�����[ _bӪ�E�-Z�8۰�kUg$�@�q [�<��X Vgn��_�������ܰF��q�Z���bnY�$C�#`� ��{-Z�hѢ�p!��<P.H���c9ٯU��s2����s�,�y�R�Cƍܽf<�� ���h�l�����K�Wd䝒�vF�E�-Z�&%E�v��{9�o-S�S�ݒ�C>�Ix��6�d��|e�l��2'�"{�4��� ^⪜N�}�p�-Z�%dt(�vA~����<ٿ��|�^ٯ6 �p�p�T��W�C�`����_y�׌��#C\���ĕ�#�hѢE����ώZT"�[���I濲������kFs{ߠ	ب�?��7  7)�2V�?�Npӌ��!(��I�;�	 �?T��hѢE��`p5	P �n��Z"Y����};ؼ�5C�����O��H4 ����?�6 `ޛ#�+	������G�Z�hѢE��A )�%����
������*Sm `} p��F� ���˂���� y�����g�kbJ v ۳��@;;ТE�-�+����G%�D�.�_��~O"�~��ަfk  >��G|Ra��^���ɪ@�2�I�/��e��ftߔ!.�[�qiNg\Vfڦ�E�-~��Z���K ��l�<^",��9F�j�)*�s��� _�mCX�p�l��fef�� ��ٕ��Qdt�d�X�n��Uc��b��y>�挍�=]����?�آE�-��'+֌֎�K ����@>["�-#/���,�w���˲_W�J呕�h�a5��ؑ�	gM0�;�F V���1�S�,L�a��|��{�a��IĮi�g�����`�Dn��l�/�r�D̈��s�-Z�!H�
�)�8	�y�ȓq�����K��ͳ4��<�'��=J$�H��~��5 �6R�$�O�%����fK�!P>O    IEND�B`�           [remap]

importer="texture"
type="StreamTexture"
path="res://.import/unnamed.png-bb1b93ae4e138561c1b371b914ec6d3f.stex"
metadata={
"vram_texture": false
}

[deps]

source_file="res://unnamed.png"
dest_files=[ "res://.import/unnamed.png-bb1b93ae4e138561c1b371b914ec6d3f.stex" ]

[params]

compress/mode=0
compress/lossy_quality=0.7
compress/hdr_mode=0
compress/bptc_ldr=0
compress/normal_map=0
flags/repeat=0
flags/filter=true
flags/mipmaps=false
flags/anisotropic=false
flags/srgb=2
process/fix_alpha_border=true
process/premult_alpha=false
process/HDR_as_SRGB=false
process/invert_color=false
stream=false
size_limit=0
detect_3d=true
svg/scale=1.0
       ECFG       _global_script_classes             _global_script_class_icons             application/config/name         hunters    application/run/main_scene          res://main_scene.tscn      application/config/icon          res://Sprites/icon.png     display/window/size/width      �     display/window/size/height      �     display/window/stretch/mode         2d     display/window/stretch/aspect         expand     input/ui_left               deadzone      ?      events              InputEventJoypadButton        resource_local_to_scene           resource_name             device            button_index         pressure          pressed           script         input/ui_right               deadzone      ?      events              InputEventJoypadButton        resource_local_to_scene           resource_name             device            button_index         pressure          pressed           script         input/ui_up               deadzone      ?      events              InputEventJoypadButton        resource_local_to_scene           resource_name             device            button_index         pressure          pressed           script         input/ui_down               deadzone      ?      events              InputEventJoypadButton        resource_local_to_scene           resource_name             device            button_index         pressure          pressed           script         input/Player2_up              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode        unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device            axis      
   axis_value       ��   script         input/Player2_down              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode        unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device            axis      
   axis_value       �?   script         input/Player2_left              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode        unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device            axis       
   axis_value       ��   script         input/Player2_right              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode        unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device            axis       
   axis_value       �?   script         input/Player1_left              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   A      unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device           axis       
   axis_value       ��   script         input/Player1_up              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   W      unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device           axis      
   axis_value       ��   script         input/Player1_down              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   S      unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device           axis      
   axis_value       �?   script         input/Player1_right              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   D      unicode           echo          script            InputEventJoypadMotion        resource_local_to_scene           resource_name             device           axis       
   axis_value       �?   script         input/Player1_fight_up`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   U      unicode           echo          script         input/Player1_fight_down`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   J      unicode           echo          script         input/Player1_fight_left`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   H      unicode           echo          script         input/Player1_fight_right`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   K      unicode           echo          script         input/Player2_fight`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode        unicode           echo          script         input/Camera_down`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   �     unicode           echo          script         input/Camera_up`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   �     unicode           echo          script         input/Camera_left`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   �     unicode           echo          script         input/Camera_right`              deadzone      ?      events              InputEventKey         resource_local_to_scene           resource_name             device            alt           shift             control           meta          command           pressed           scancode   �     unicode           echo          script         locale/locale_filter                       )   rendering/environment/default_environment          res://default_env.tres                