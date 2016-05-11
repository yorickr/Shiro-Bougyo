#ifndef ENTITY_H
#define ENTITY_H

class Entity {
	public:
		virtual void Init() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

	protected:
		Entity() { }
};
#endif