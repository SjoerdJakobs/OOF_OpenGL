#pragma once

class StandardObject
{
protected:
    StandardObject();
    StandardObject(int priority);
	StandardObject(bool startsActivated, bool usesInput, bool usesUpdate, bool usesFixedUpdate, bool usesRenderer, bool usesImGui, bool usesDebugRenderer, int inputPriority, int updatePriority, int renderPriority, int imGuiPriority);
    
    //Program* m_program = Program::getInstance();
    
    bool m_pauseImmune;         //if this is true then normal pause will have no effect on this object, no object can escape truepause though 
    bool m_isPersistentObject;  //if this is true then this object wont be destroyed when switching scenes
	
	//bools that tell which loops are used by this object
    bool m_usesInput;           //tells if this object use the input loop
    bool m_usesUpdate;          //tells if this object use the update loop
    bool m_usesFixedUpdate;     //tells if this object use the fixedUpdate loop
    bool m_usesRenderer;        //tells if this object use the render loop
    bool m_usesDebugRenderer;   //tells if this object use the debugRender loop
    bool m_usesImGui;           //tells if this object use the ImGui loop

    unsigned int m_inputPriority;   //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_updatePriority;  //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_renderPriority;  //lower goes first, the object created first goes first if priority numbers are the same
    unsigned int m_imGuiPriority;   //lower goes first, the object created first goes first if priority numbers are the same

	bool m_shouldDestruct;  //should this object be destroyed at the end of the loop
	bool m_shouldBeActive;	//says if the object should be active or not
	bool m_isActiveState;	//is the actual active/inactive state of the object

public:
    ~StandardObject();

    void AddToLists();      //adds this object to its appropriate list

    void RemoveFromLists(); //removes this object from lists that it is in if the corresponding bool is on false
	
    /**
     * this is called when the object gets created
     * after the constructor but before the awake and the loops
     */
    virtual void Start();

    /**
     * this is called when the object gets set to active
     * if the object is created active awake will run right after the start method but before the loops
     * if the object is created inactive awake will run when the object is set to active which happens right after the program loops
     * Awake will run every time the object goes from inactive to active
     */
    virtual void Awake();

    /**
     * this is called when the object gets set to inactive
     * Sleep will run every time the object goes from active to inactive which happens right after the program loops
     */
    virtual void Sleep();

    virtual void Destroy();

    virtual void Input(double deltaTime);
	
    virtual void Update(double deltaTime);
	
    virtual void Render(double deltaTime);
	
    virtual void ImGuiRender(double deltaTime);
	
    virtual void DebugRender(double deltaTime);

    bool GetUsesInput()          const{ return m_usesInput; }
    bool GetUsesUpdate()         const{ return m_usesUpdate; }
    bool GetUsesFixedUpdate()    const{ return m_usesFixedUpdate; }
    bool GetUsesRenderer()       const{ return m_usesRenderer; }
    bool GetUsesDebugRenderer()  const{ return m_usesDebugRenderer; }
    bool GetUsesImGui()          const{ return m_usesImGui; }
	
	bool GetShouldDestruct()    const { return m_shouldDestruct; }
	bool IsShouldBeActive()     const { return m_shouldBeActive; }
	bool IsActiveState()		const { return m_isActiveState; }
    bool IsPauseImmune()        const { return m_pauseImmune; }
    bool IsPersistentObject()   const { return m_isPersistentObject; }
    
	void SetShouldBeActive   (bool b) { m_shouldBeActive = b; }
	void SetActiveState      (bool b) { m_isActiveState  = b; }
};
