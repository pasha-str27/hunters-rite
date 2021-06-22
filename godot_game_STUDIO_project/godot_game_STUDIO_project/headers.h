#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <functional>
#include <math.h>
#include <map>

//Godot includes
#include <TextureRect.hpp>
#include <ResourceLoader.hpp>
#include <Godot.hpp>
#include <Button.hpp>
#include <TextureButton.hpp>
#include <KinematicBody2D.hpp>
#include <CollisionObject2D.hpp>
#include <Node2D.hpp>
#include <Node.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <Vector2.hpp>
#include <Area2D.hpp>
#include <Sprite.hpp>
#include <OS.hpp>
#include <Timer.hpp>
#include <RandomNumberGenerator.hpp>
#include <Camera2D.hpp>
#include <InputEvent.hpp>
#include <TileMap.hpp>
#include <Tree.hpp>
#include <Label.hpp>
#include <Array.hpp>
#include <ScrollContainer.hpp>
#include <ProgressBar.hpp>
#include <InputEventKey.hpp>
#include <AnimationPlayer.hpp>
#include <Particles2D.hpp>
#include <ParticlesMaterial.hpp>
#include <AnimatedSprite.hpp>
#include <SpriteFrames.hpp>
#include <SceneTree.hpp>
#include <VBoxContainer.hpp>
#include <SceneTree.hpp>
#include <Texture.hpp>
#include <AudioServer.hpp>
#include <AudioStreamPlayer2D.hpp>
#include <AudioStream.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Slider.hpp>
#include <Dictionary.hpp>
#include <ResourceSaver.hpp>
#include <Control.hpp>
#include <MarginContainer.hpp>

using namespace godot;

//project includes
#include "IPlayer.h"
#include "PlayerData.h"
#include "Player1.h"
#include "Player2.h"
#include "PlayerController.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "PlayerProduce.h"
#include "ProducePlayer1.h"
#include "ProducePlayer2.h"
#include "Sword.h"
#include "CameraController.h"
#include "Spike.h"
#include "SlimeAI.h"
#include "BatAI.h"
#include "SpiderAI.h"
#include "Enemies.h"
#include "FlowerAI.h"
#include "Item.h"
#include "ReviveZone.h"
#include "InputReviveManager.h"
#include "StatueMeleeAI.h"
#include "StatueShootAI.h"
#include "FadeAnimation.h"
#include "PlayersContainer.h"
#include "RoomStats.h"
#include "MenuButtons.h"
#include "AudioEffect.h"
#include "ParticlesDestroyer.h"
#include "ExitHandler.h"
#include "Preloader.h"
#include "SpawnEnemyController.h"
#include "ItemsContainer.h"
#include "ItemGenerator.h"
#include "CustomExtensions.h"
#include "MagnitZone.h"
#include "Room.h"
#include "LevelGenerator.h"
#include "MiniMapController.h"
#include "Key.h"
